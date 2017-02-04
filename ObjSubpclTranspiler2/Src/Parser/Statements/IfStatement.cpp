#include "IfStatement.h"

#include <Parser/Expressions/BaseExpression.h>

using namespace Parser;

IfStatement::IfStatement(BaseExpression* p_IfExpression, IStatement* p_ThenStatement, IStatement* p_ElseStatement) :
	m_IfExpression(p_IfExpression),
	m_ThenStatement(p_ThenStatement),
	m_ElseStatement(p_ElseStatement)
{

}

void IfStatement::Generate()
{

}