#include "ClassVariableType.h"

#include <Parser/Identifier.h>
#include <Parser/Expressions/IExpression.h>

using namespace Parser;

ClassVariableType::ClassVariableType(Identifier* p_Type, ExpressionSeq* p_Arguments) :
	m_Type(p_Type),
	m_Arguments(p_Arguments)
{
}

void ClassVariableType::Generate()
{

}