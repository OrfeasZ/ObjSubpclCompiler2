#include "VariableType.h"

#include "ArrayVariableType.h"

#include <Parser/Class/ClassVariablePointerType.h>
#include <Parser/Class/ClassVariableType.h>
#include <Parser/Identifier.h>

using namespace Parser;

VariableType::VariableType(VariableTypes::type p_Type) :
	m_Type(p_Type)
{

}

std::string VariableType::ToString()
{
	switch (m_Type)
	{
	case VariableTypes::Integer:
		return "long";

	case VariableTypes::Real:
		return "double";

	default:
		return "";
	}
}

std::string VariableType::GetTypeFromVariableType(VariableType* p_Type)
{
	if (p_Type == nullptr)
		return "";

	if (p_Type->m_Type == VariableTypes::Class)
	{
		auto s_Type = (ClassVariableType*) p_Type;
		return s_Type->m_ClassType->m_Name;
	}

	if (p_Type->m_Type == VariableTypes::ClassPointer)
	{
		auto s_Type = (ClassVariablePointerType*) p_Type;
		return s_Type->m_ClassType->m_Name;
	}

	if (p_Type->m_Type == VariableTypes::Array)
	{
		auto s_Type = (ArrayVariableType*) p_Type;
		return GetTypeFromVariableType(s_Type->m_InnerType);
	}

	return "";
}