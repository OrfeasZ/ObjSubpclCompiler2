#include "VariableType.h"

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