#include "ClassDefinition.h"

#include "ClassHeader.h"
#include <Parser/VariableDeclaration.h>
#include "ClassBody.h"
#include <Parser/Identifier.h>

#include <Parser/Procedure/Procedure.h>
#include <Parser/Procedure/ProcedureHeader.h>
#include <Parser/VariableType.h>
#include <Parser/ArrayVariableType.h>
#include <Parser/Expressions/Integer.h>

#include <Managers/ClassManager.h>
#include <Managers/CodeManager.h>

#include <Util/Utils.h>

#include <algorithm>

using namespace Parser;

ClassDefinition::ClassDefinition(ClassHeader* p_Header, VariableSeq* p_Variables, ClassBody* p_Body) :
	m_Header(p_Header),
	m_Variables(p_Variables),
	m_Body(p_Body)
{
	Managers::ClassManager::RegisterClass(this);
}

void ClassDefinition::GenerateDefinitions()
{
	// Get the parent class (if there is one).
	ClassDefinition* s_Parent = nullptr;

	if (m_Header->m_Extends != nullptr)
	{
		s_Parent = Managers::ClassManager::GetClass(m_Header->m_Extends->m_Name);

		// If we have a parent set but he doesn't exist then something is wrong.
		if (s_Parent == nullptr)
			throw new std::exception(("Could not find parent '" + m_Header->m_Extends->m_Name + "' for class '" + m_Header->m_Name->m_Name + "'.").c_str());
	}

	// Write our forward declaration;
	Managers::CodeManager::Writer()->WriteLnInd("struct " + m_Header->m_Name->m_Name + "_t;");
	Managers::CodeManager::Writer()->WriteLn();

	// Generate code for this class.
	GenerateVtable(s_Parent);
	GenerateStruct(s_Parent);
}

void ClassDefinition::GenerateBody()
{
	// Get the parent class (if there is one).
	ClassDefinition* s_Parent = nullptr;

	if (m_Header->m_Extends != nullptr)
		s_Parent = Managers::ClassManager::GetClass(m_Header->m_Extends->m_Name);

	// Generate code for this class.
	GenerateConstructor(s_Parent);
	GenerateMethods(s_Parent);
}

std::vector<Procedure*> ClassDefinition::GetMethods(ProcedureType::type p_Type)
{
	std::vector<Procedure*> s_Methods;

	if (m_Body->m_Procedures == nullptr)
		return s_Methods;

	for (auto s_Method : *m_Body->m_Procedures)
		if (s_Method->m_Type == p_Type)
			s_Methods.push_back(s_Method);

	return s_Methods;
}

bool ClassDefinition::IsAbstract()
{
	return GetMethods(ProcedureType::Abstract).size() > 0;
}

bool ClassDefinition::HasMember(const std::string& p_Name)
{
	if (m_Variables == nullptr)
		return false;

	for (auto s_Variable : *m_Variables)
		for (auto s_ID : *s_Variable->m_IDs)
			if (s_ID->m_Name == p_Name)
				return true;

	// Search the parent variables.
	if (m_Header->m_Extends == nullptr)
		return false;

	auto s_Parent = Managers::ClassManager::GetClass(m_Header->m_Extends->m_Name);

	// Not sure if we would ever get here, but might as well.
	if (s_Parent == nullptr)
		return false;

	return s_Parent->HasMember(p_Name);
}

bool ClassDefinition::HasMethod(const std::string& p_Name)
{
	for (auto s_Method : GetMethods(ProcedureType::Standard))
		if (s_Method->m_Header->m_Name->m_Name == p_Name)
			return true;

	for (auto s_Method : GetMethods(ProcedureType::Dynamic))
		if (s_Method->m_Header->m_Name->m_Name == p_Name)
			return true;

	// Search the parent methods.
	if (m_Header->m_Extends == nullptr)
		return false;

	auto s_Parent = Managers::ClassManager::GetClass(m_Header->m_Extends->m_Name);

	// Not sure if we would ever get here, but might as well.
	if (s_Parent == nullptr)
		return false;

	return s_Parent->HasMethod(p_Name);
}

void ClassDefinition::GenerateVtable(ClassDefinition* p_Parent)
{
	// Get methods and sort alphabetically (for sanity's sake).
	// TODO: Do we also need the methods of our parent?
	auto s_Methods = GetMethods(ProcedureType::Dynamic);

	if (s_Methods.size() == 0)
		return;

	std::sort(s_Methods.begin(), s_Methods.end(), [](const Procedure* p_Left, const Procedure* p_Right) 
	{ 
		return p_Left->m_Header->m_Name->m_Name < p_Right->m_Header->m_Name->m_Name; 
	});

	// Generate method typedefs and forward declarations.
	// TODO: Make sure we don't have any additional virtual functions or handle them appropriately.
	for (auto s_Method : s_Methods)
	{
		Managers::CodeManager::Writer()->WriteInd("typedef void (*" + m_Header->m_Name->m_Name + "__" + s_Method->m_Header->m_Name->m_Name + "_t)");

		auto s_Parameters = s_Method->m_Header->GetParameters();
		s_Parameters.insert(s_Parameters.begin(), "struct " + m_Header->m_Name->m_Name + "_t* th");

		auto s_FinalParameters = Util::Utils::Join(s_Parameters, ", ");

		Managers::CodeManager::Writer()->WriteLn("(" + s_FinalParameters + ");");

		// Write forward declaration.
		Managers::CodeManager::Writer()->WriteLnInd("void " + m_Header->m_Name->m_Name + "__" + s_Method->m_Header->m_Name->m_Name + "(" + s_FinalParameters + ");");
		Managers::CodeManager::Writer()->WriteLn();
	}
	
	// Write the vtable structure.
	Managers::CodeManager::Writer()->WriteLnInd("struct " + m_Header->m_Name->m_Name + "_vtbl_t");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	for (auto s_Method : s_Methods)
		Managers::CodeManager::Writer()->WriteLnInd(m_Header->m_Name->m_Name + "__" + s_Method->m_Header->m_Name->m_Name + "_t " + s_Method->m_Header->m_Name->m_Name + ";");

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteLnInd("};");
	Managers::CodeManager::Writer()->WriteLn();

	// Write the static vtable variable.
	Managers::CodeManager::Writer()->WriteLnInd("static const struct " + m_Header->m_Name->m_Name + "_vtbl_t " + m_Header->m_Name->m_Name + "_vtblptr = ");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	for (auto s_Method : s_Methods)
	{
		Managers::CodeManager::Writer()->WriteInd("." + s_Method->m_Header->m_Name->m_Name + " = ");
		Managers::CodeManager::Writer()->Write("(" + m_Header->m_Name->m_Name + "__" + s_Method->m_Header->m_Name->m_Name + "_t) " + m_Header->m_Name->m_Name + "__" + s_Method->m_Header->m_Name->m_Name);
		Managers::CodeManager::Writer()->WriteLn(",");
	}

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteLnInd("};");
	Managers::CodeManager::Writer()->WriteLn();
}

void ClassDefinition::GenerateStruct(ClassDefinition* p_Parent)
{
	Managers::CodeManager::Writer()->WriteLnInd("struct " + m_Header->m_Name->m_Name + "_t");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	// Write our vtable variable.
	if (GetMethods(ProcedureType::Dynamic).size() > 0)
	{
		// TODO: Write only if our parent doesn't have a vtable himself.
		Managers::CodeManager::Writer()->WriteLnInd("struct " + m_Header->m_Name->m_Name + "_vtbl_t* vtbl;");
	}

	// TODO: Make sure we don't have any additional virtual functions or handle them appropriately.
	if (p_Parent != nullptr)
		Managers::CodeManager::Writer()->WriteLnInd("struct " + p_Parent->m_Header->m_Name->m_Name + "_t; // Base class.");

	// Write our variables.
	if (m_Variables)
	{
		for (auto s_Variable : *m_Variables)
		{
			for (auto s_ID : *s_Variable->m_IDs)
			{
				Managers::CodeManager::Writer()->WriteInd(s_Variable->m_Type->ToString() + " " + s_ID->m_Name);

				// If this is an array then add the element count after the variable name.
				if (s_Variable->m_Type->m_Type == VariableTypes::Array)
				{
					auto s_Type = (ArrayVariableType*) s_Variable->m_Type;
					Managers::CodeManager::Writer()->Write("[");
					Managers::CodeManager::Writer()->Write(s_Type->m_ElementCount->m_Value);
					Managers::CodeManager::Writer()->Write("]");
				}

				Managers::CodeManager::Writer()->WriteLn(";");
			}
		}
	}

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteLnInd("};");
	Managers::CodeManager::Writer()->WriteLn();
}

void ClassDefinition::GenerateConstructor(ClassDefinition* p_Parent)
{

}

void ClassDefinition::GenerateMethods(ClassDefinition* p_Parent)
{

}
