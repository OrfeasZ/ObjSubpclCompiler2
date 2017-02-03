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

using namespace Parser;

ClassDefinition::ClassDefinition(ClassHeader* p_Header, VariableSeq* p_Variables, ClassBody* p_Body) :
	m_Header(p_Header),
	m_Variables(p_Variables),
	m_Body(p_Body)
{
	Managers::ClassManager::RegisterClass(this);
}

void ClassDefinition::Generate()
{
	ClassDefinition* s_Parent = nullptr;

	if (m_Header->m_Extends != nullptr)
	{
		s_Parent = Managers::ClassManager::GetClass(m_Header->m_Extends->m_Name);

		// If we have a parent set but he doesn't exist then something is wrong.
		if (s_Parent == nullptr)
			throw new std::exception(("Could not find parent '" + m_Header->m_Extends->m_Name + "' for class '" + m_Header->m_Name->m_Name + "'.").c_str());
	}

	// Generate code for this class.
	GenerateVtable(s_Parent);
	GenerateStruct(s_Parent);
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

}

void ClassDefinition::GenerateStruct(ClassDefinition* p_Parent)
{
	Managers::CodeManager::Writer()->WriteLnInd("struct " + m_Header->m_Name->m_Name);
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	if (p_Parent != nullptr)
	{
		Managers::CodeManager::Writer()->WriteLnInd("struct " + p_Parent->m_Header->m_Name->m_Name + "_t; // Base class.");
	}
	else if (GetMethods(ProcedureType::Dynamic).size() > 0)
	{
		// Write our vtable variable.
		Managers::CodeManager::Writer()->WriteLnInd("struct " + m_Header->m_Name->m_Name + "_vtbl_t* vtbl;");
	}

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
	Managers::CodeManager::Writer()->WriteLnInd("} " + m_Header->m_Name->m_Name + "_t;");
}

void ClassDefinition::GenerateConstructor(ClassDefinition* p_Parent)
{

}

void ClassDefinition::GenerateMethods(ClassDefinition* p_Parent)
{

}
