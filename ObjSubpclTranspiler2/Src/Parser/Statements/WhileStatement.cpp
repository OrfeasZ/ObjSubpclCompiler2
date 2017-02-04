#include "WhileStatement.h"

#include <Parser/Expressions/BaseExpression.h>

using namespace Parser;

WhileStatement::WhileStatement(BaseExpression* p_WhileExpression, IStatement* p_DoStatement) :
	m_WhileExpression(p_WhileExpression),
	m_DoStatement(p_DoStatement)
{

}

void WhileStatement::Generate()
{

}