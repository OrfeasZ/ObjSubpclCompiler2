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
	m_WhileExpression->SetParents(this);
	m_DoStatement->SetParents(this);
	
	Managers::CodeManager::Writer()->Write("while (");
	m_WhileExpression->Generate();
	Managers::CodeManager::Writer()->WriteLn(")");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	m_DoStatement->Generate();

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteInd("}");
}