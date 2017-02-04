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
	m_IfExpression->SetParents(this);
	m_ThenStatement->SetParents(this);

	if (m_ElseStatement)
		m_ElseStatement->SetParents(this);

	Managers::CodeManager::Writer()->Write("if (");
	m_IfExpression->Generate();
	Managers::CodeManager::Writer()->WriteLn(")");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	Managers::CodeManager::Writer()->WriteIndent();
	m_ThenStatement->Generate();
	Managers::CodeManager::Writer()->WriteLn(";");

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteInd("}");

	if (m_ElseStatement == nullptr)
		return;
	
	Managers::CodeManager::Writer()->WriteLn();
	Managers::CodeManager::Writer()->WriteLnInd("else");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	Managers::CodeManager::Writer()->WriteIndent();
	m_ElseStatement->Generate();
	Managers::CodeManager::Writer()->WriteLn(";");

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteInd("}");
}