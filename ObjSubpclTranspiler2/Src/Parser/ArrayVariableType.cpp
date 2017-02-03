#include "ArrayVariableType.h"

#include <Parser/Expressions/Integer.h>

using namespace Parser;

ArrayVariableType::ArrayVariableType(VariableType* p_InnerType, Integer* p_ElementCount) :
	VariableType(VariableTypes::Array),
	m_InnerType(p_InnerType),
	m_ElementCount(p_ElementCount)
{

}

void ArrayVariableType::Generate()
{

}