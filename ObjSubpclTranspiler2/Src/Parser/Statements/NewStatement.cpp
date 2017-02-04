#include "NewStatement.h"

#include <Parser/Expressions/BaseExpression.h>

using namespace Parser;

NewStatement::NewStatement(BaseExpression* p_LeftExpression, Identifier* p_ClassName, ExpressionSeq* p_Arguments) :
	m_LeftExpression(p_LeftExpression),
	m_ClassName(p_ClassName),
	m_Arguments(p_Arguments)
{

}

void NewStatement::Generate()
{

}