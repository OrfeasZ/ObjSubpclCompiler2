#include "AssignmentStatement.h"

#include "IExpression.h"

using namespace Parser;

AssignmentStatement::AssignmentStatement(IExpression* p_LeftExpression, IExpression* p_RightExpression) :
	m_LeftExpression(p_LeftExpression),
	m_RightExpression(p_RightExpression)
{

}

void AssignmentStatement::Generate()
{

}