#include "ClassDefinition.h"

#include "ClassHeader.h"
#include <Parser/VariableDeclaration.h>
#include "ClassBody.h"
#include "ClassVariableType.h"
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

	// Generate code for this class.
	GenerateStruct(s_Parent);
	GenerateVtable(s_Parent);
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

bool ClassDefinition::HasMethod(const std::string& p_Name, bool& p_Virtual, bool p_CheckParent)
{
	p_Virtual = false;

	for (auto s_Method : GetMethods(ProcedureType::Standard))
		if (s_Method->m_Header->m_Name->m_Name == p_Name)
			return true;

	for (auto s_Method : GetMethods(ProcedureType::Dynamic))
	{
		if (s_Method->m_Header->m_Name->m_Name == p_Name)
		{
			p_Virtual = true;
			return true;
		}
	}

	if (!p_CheckParent)
		return false;

	// Search the parent methods.
	if (m_Header->m_Extends == nullptr)
		return false;

	auto s_Parent = Managers::ClassManager::GetClass(m_Header->m_Extends->m_Name);

	// Not sure if we would ever get here, but might as well.
	if (s_Parent == nullptr)
		return false;

	return s_Parent->HasMethod(p_Name, p_Virtual, p_CheckParent);
}

void ClassDefinition::GenerateVtable(ClassDefinition* p_Parent)
{
	// TODO: Split these into separate functions when I stop being lazy.

	// Get methods and sort alphabetically (for sanity's sake).
	// TODO: Do we also need the methods of our parent?
	// TODO: Handle abstract as pure virtual.
	auto s_Methods = GetMethods(ProcedureType::Dynamic);

	if (s_Methods.size() == 0)
		return;

	std::sort(s_Methods.begin(), s_Methods.end(), [](const Procedure* p_Left, const Procedure* p_Right) 
	{ 
		return p_Left->m_Header->m_Name->m_Name < p_Right->m_Header->m_Name->m_Name; 
	});

	// Generate method typedefs and forward declarations.
	// TODO: Make sure we don't have any additional virtual functions or handle them appropriately.
	Managers::CodeManager::Writer()->WriteLnInd("// Vtable method descriptors for class " + m_Header->m_Name->m_Name);

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
	Managers::CodeManager::Writer()->WriteLnInd("// Vtable descriptor for class " + m_Header->m_Name->m_Name);
	Managers::CodeManager::Writer()->WriteLnInd("struct " + m_Header->m_Name->m_Name + "_vtbl_t");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	for (auto s_Method : s_Methods)
		Managers::CodeManager::Writer()->WriteLnInd(m_Header->m_Name->m_Name + "__" + s_Method->m_Header->m_Name->m_Name + "_t " + s_Method->m_Header->m_Name->m_Name + ";");

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteLnInd("};");
	Managers::CodeManager::Writer()->WriteLn();

	// Write the static vtable variable.
	Managers::CodeManager::Writer()->WriteLnInd("// Static vtable for class " + m_Header->m_Name->m_Name);
	Managers::CodeManager::Writer()->WriteLnInd("static struct " + m_Header->m_Name->m_Name + "_vtbl_t " + m_Header->m_Name->m_Name + "_vtblptr = ");
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
		Managers::CodeManager::Writer()->WriteLnInd("void* vtbl;");
	}

	// TODO: Make sure we don't have any additional virtual functions or handle them appropriately.
	if (p_Parent != nullptr)
		Managers::CodeManager::Writer()->WriteLnInd("struct " + p_Parent->m_Header->m_Name->m_Name + "_t; // Base class");

	// Write our variables.
	if (m_Variables)
	{
		for (auto s_Variable : *m_Variables)
		{
			// Make sure we're not trying to instantiate an abstract class.
			if (s_Variable->m_Type->m_Type == VariableTypes::Class)
			{
				auto s_ClassType = (ClassVariableType*) s_Variable->m_Type;
				auto s_ClassTypeClass = Managers::ClassManager::GetClass(s_ClassType->m_ClassType->m_Name);

				if (s_ClassTypeClass == nullptr)
					throw new std::exception(("Could not find class '" + s_ClassType->m_ClassType->m_Name + "' used for a variable.").c_str());

				if (s_ClassTypeClass->IsAbstract())
					throw new std::exception(("Cannot instantiate a variable of abstract type '" + s_ClassType->m_ClassType->m_Name + "'.").c_str());
			}

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
	auto s_Parameters = m_Body->m_Constructor->m_Header->GetParameters();
	s_Parameters.insert(s_Parameters.begin(), "struct " + m_Header->m_Name->m_Name + "_t* th");

	auto s_FinalParameters = Util::Utils::Join(s_Parameters, ", ");

	Managers::CodeManager::Writer()->WriteLnInd("void " + m_Header->m_Name->m_Name + "__ctor(" + s_FinalParameters + ")");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	// Clear our memory.
	Managers::CodeManager::Writer()->WriteLnInd("memset(th, 0x00, sizeof(struct " + m_Header->m_Name->m_Name + "_t));");

	// Init our vtable.
	if (GetMethods(ProcedureType::Dynamic).size() > 0)
		Managers::CodeManager::Writer()->WriteLnInd("th->vtbl = &" + m_Header->m_Name->m_Name + "_vtblptr;");

	// TODO: Initialize class member variables.
	// TODO: Generate constructor scoped variables.
	// TODO: Generate constructor statements.

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteLnInd("}");
	Managers::CodeManager::Writer()->WriteLn();
}

void ClassDefinition::GenerateMethods(ClassDefinition* p_Parent)
{
	for (auto s_Method : GetMethods(ProcedureType::Dynamic))
		GenerateMethod(s_Method);

	for (auto s_Method : GetMethods(ProcedureType::Standard))
		GenerateMethod(s_Method);
}

void ClassDefinition::GenerateMethod(Procedure* p_Procedure)
{
	auto s_Parameters = p_Procedure->m_Header->GetParameters();
	s_Parameters.insert(s_Parameters.begin(), "struct " + m_Header->m_Name->m_Name + "_t* th");

	auto s_FinalParameters = Util::Utils::Join(s_Parameters, ", ");

	Managers::CodeManager::Writer()->WriteLnInd("void " + m_Header->m_Name->m_Name + "__" + p_Procedure->m_Header->m_Name->m_Name + "(" + s_FinalParameters + ")");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	// TODO: Generate method scoped variables.
	// TODO: Generate method statements.

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteLnInd("}");
	Managers::CodeManager::Writer()->WriteLn();
}
