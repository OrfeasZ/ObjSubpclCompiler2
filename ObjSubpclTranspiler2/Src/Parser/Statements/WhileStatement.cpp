#include "WhileStatement.h"

#include <Parser/Expressions/IExpression.h>

using namespace Parser;

WhileStatement::WhileStatement(IExpression* p_WhileExpression, IStatement* p_DoStatement) :
	m_WhileExpression(p_WhileExpression),
	m_DoStatement(p_DoStatement)
{

}