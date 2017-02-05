#include "VariableDeclaration.h"

#include "Identifier.h"
#include "VariableType.h"

#include "ArrayVariableType.h"
#include <Parser/Class/ClassDefinition.h>
#include <Parser/Class/ClassHeader.h>
#include <Parser/Class/ClassVariableType.h>
#include <Parser/Class/ClassVariablePointerType.h>
#include <Parser/Expressions/BaseExpression.h>
#include <Parser/Expressions/Integer.h>

#include <Managers/CodeManager.h>
#include <Managers/ClassManager.h>

#include <Util/Utils.h>

using namespace Parser;

VariableDeclaration::VariableDeclaration(IDSeq* p_IDs, VariableType* p_Type) :
	m_IDs(p_IDs),
	m_Type(p_Type)
{

}

void VariableDeclaration::Generate()
{
	for (auto s_ID : *m_IDs)
	{
		switch (m_Type->m_Type)
		{
		case VariableTypes::Integer:
			Managers::CodeManager::Writer()->WriteLnInd("long " + s_ID->m_Name + ";");
			break;

		case VariableTypes::Real:
			Managers::CodeManager::Writer()->WriteLnInd("double " + s_ID->m_Name + ";");
			break;

		case VariableTypes::ClassPointer:
			GenerateClassPointer(s_ID->m_Name);
			break;

		case VariableTypes::Class:
			GenerateClass(s_ID->m_Name);
			break;

		case VariableTypes::Array:
			GenerateArray(s_ID->m_Name);
			break;
		}
	}
}

void VariableDeclaration::GenerateClassPointer(const std::string& p_Name)
{
	auto s_Type = (ClassVariablePointerType*) m_Type;
	Managers::CodeManager::Writer()->WriteLnInd("struct " + s_Type->m_ClassType->m_Name + "_t* " + p_Name + " = NULL;");
}

void VariableDeclaration::GenerateClass(const std::string& p_Name, ClassVariableType* p_Type)
{
	auto s_Type = p_Type;
	bool s_WriteType = p_Type == nullptr;

	if (s_Type == nullptr)
		s_Type = (ClassVariableType*) m_Type;

	auto s_Class = Managers::ClassManager::GetClass(s_Type->m_ClassType->m_Name);

	if (s_Class == nullptr)
		throw std::exception(("Could not find class '" + s_Type->m_ClassType->m_Name + "' used for variable '" + p_Name + "'.").c_str());

	if (s_Class->IsAbstract())
		throw std::exception(("Cannot instantiate abstract class '" + s_Type->m_ClassType->m_Name + "'.").c_str());

	std::vector<std::string> s_Arguments;

	// Serialize our arguments.
	if (s_Type->m_Arguments)
	{
		for (auto s_Expression : *s_Type->m_Arguments)
		{
			s_Expression->SetParents(this);
			s_Arguments.push_back(s_Expression->ToString());
		}
	}

	std::string s_ClassName = s_Class->m_Header->m_Name->m_Name;
	std::string s_ClassType = s_ClassName + "_t";
	std::string s_ClassCtor = s_ClassName + "__ctor";

	// Add the variable itself as the first argument.
	s_Arguments.insert(s_Arguments.begin(), "(struct " + s_ClassType + "*) " + p_Name);

	// Allocate the member.
	if (s_WriteType)
		Managers::CodeManager::Writer()->WriteInd("struct " + s_ClassType + "* ");
	else
		Managers::CodeManager::Writer()->WriteIndent();

	Managers::CodeManager::Writer()->WriteLn(p_Name + " = malloc(sizeof(struct " + s_ClassType + "));");

	// Call the constructor.
	Managers::CodeManager::Writer()->WriteLnInd(s_ClassCtor + "(" + Util::Utils::Join(s_Arguments, ", ") + ");");
}

void VariableDeclaration::GenerateArray(const std::string& p_Name)
{
	auto s_Type = (ArrayVariableType*) m_Type;

	switch (s_Type->m_InnerType->m_Type)
	{
	case VariableTypes::Integer:
		Managers::CodeManager::Writer()->WriteLnInd("long " + p_Name + "[" + std::to_string(s_Type->m_ElementCount->m_Value) + "];");
		break;

	case VariableTypes::Real:
		Managers::CodeManager::Writer()->WriteLnInd("double " + p_Name + "[" + std::to_string(s_Type->m_ElementCount->m_Value) + "];");
		break;

	case VariableTypes::ClassPointer:
	{
		auto s_ClassType = (ClassVariablePointerType*)s_Type->m_InnerType;
		Managers::CodeManager::Writer()->WriteLnInd("struct " + s_ClassType->m_ClassType->m_Name + "_t* " + p_Name + "[" + std::to_string(s_Type->m_ElementCount->m_Value) + "];");
		break;
	}

	case VariableTypes::Class:
	{
		auto s_ClassType = (ClassVariableType*) s_Type->m_InnerType;
		Managers::CodeManager::Writer()->WriteLnInd("struct " + s_ClassType->m_ClassType->m_Name + "_t* " + p_Name + "[" + std::to_string(s_Type->m_ElementCount->m_Value) + "];");

		for (int64_t i = 0; i < s_Type->m_ElementCount->m_Value; ++i)
			GenerateClass(p_Name + "[" + std::to_string(i) + "]", s_ClassType);

		break;
	}

	case VariableTypes::Array:
		throw std::exception("Multi-dimensional arrays are currently unsupported.");
	}
}

void VariableDeclaration::Initialize()
{
	for (auto s_ID : *m_IDs)
	{
		switch (m_Type->m_Type)
		{
		case VariableTypes::Integer:
		case VariableTypes::Real:
		case VariableTypes::ClassPointer:
			break;

		case VariableTypes::Class:
			InitializeClass(s_ID->m_Name);
			break;

		case VariableTypes::Array:
			InitializeArray(s_ID->m_Name);
			break;
		}
	}
}

void VariableDeclaration::InitializeClass(const std::string& p_Name, ClassVariableType* p_Type)
{
	auto s_Type = p_Type;

	if (s_Type == nullptr)
		s_Type = (ClassVariableType*) m_Type;

	auto s_Class = Managers::ClassManager::GetClass(s_Type->m_ClassType->m_Name);

	if (s_Class == nullptr)
		throw std::exception(("Could not find class '" + s_Type->m_ClassType->m_Name + "' used for variable '" + p_Name + "'.").c_str());

	if (s_Class->IsAbstract())
		throw std::exception(("Cannot instantiate abstract class '" + s_Type->m_ClassType->m_Name + "'.").c_str());

	std::vector<std::string> s_Arguments;

	// Serialize our arguments.
	if (s_Type->m_Arguments)
	{
		for (auto s_Expression : *s_Type->m_Arguments)
		{
			s_Expression->SetParents(this);
			s_Arguments.push_back(s_Expression->ToString());
		}
	}

	std::string s_ClassName = s_Class->m_Header->m_Name->m_Name;
	std::string s_ClassType = s_ClassName + "_t";
	std::string s_ClassCtor = s_ClassName + "__ctor";

	// Add the variable itself as the first argument.
	if (m_ParentClass != nullptr)
		s_Arguments.insert(s_Arguments.begin(), "(struct " + s_ClassType + "*) th->" + p_Name);
	else
		s_Arguments.insert(s_Arguments.begin(), "(struct " + s_ClassType + "*) " + p_Name);

	// Allocate the member.
	if (m_ParentClass != nullptr)
		Managers::CodeManager::Writer()->WriteInd("th->");
	else
		Managers::CodeManager::Writer()->WriteIndent();

	Managers::CodeManager::Writer()->WriteLn(p_Name + " = malloc(sizeof(struct " + s_ClassType + "));");

	// Call the constructor.
	Managers::CodeManager::Writer()->WriteLnInd(s_ClassCtor + "(" + Util::Utils::Join(s_Arguments, ", ") + ");");
}

void VariableDeclaration::InitializeArray(const std::string& p_Name)
{
	auto s_Type = (ArrayVariableType*) m_Type;

	switch (s_Type->m_InnerType->m_Type)
	{
	case VariableTypes::Integer:
	case VariableTypes::Real:
	case VariableTypes::ClassPointer:
		break;

	case VariableTypes::Class:
	{
		auto s_ClassType = (ClassVariableType*) s_Type->m_InnerType;

		for (int64_t i = 0; i < s_Type->m_ElementCount->m_Value; ++i)
			InitializeClass(p_Name + "[" + std::to_string(i) + "]", s_ClassType);

		break;
	}

	case VariableTypes::Array:
		throw std::exception("Multi-dimensional arrays are currently unsupported.");
	}
}

bool VariableSeq::HasVariable(const std::string& p_Name, VariableType*& p_Type)
{
	for (auto s_Variable : *this)
	{
		for (auto s_ID : *s_Variable->m_IDs)
		{
			if (s_ID->m_Name == p_Name)
			{
				p_Type = s_Variable->m_Type;
				return true;
			}
		}
	}

	return false;
}