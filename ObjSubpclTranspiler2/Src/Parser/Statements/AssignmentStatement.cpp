#include "AssignmentStatement.h"

#include <Parser/Expressions/BaseExpression.h>

#include <Managers/CodeManager.h>

using namespace Parser;

AssignmentStatement::AssignmentStatement(BaseExpression* p_LeftExpression, BaseExpression* p_RightExpression) :
	m_LeftExpression(p_LeftExpression),
	m_RightExpression(p_RightExpression)
{

}

void AssignmentStatement::Generate()
{
	m_LeftExpression->SetParents(this);
	m_RightExpression->SetParents(this);

	m_LeftExpression->Generate();
	Managers::CodeManager::Writer()->Write(" = ");
	m_RightExpression->Generate();
}