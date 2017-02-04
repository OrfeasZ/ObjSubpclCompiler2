#include "AssignmentStatement.h"

#include <Parser/Expressions/BaseExpression.h>

using namespace Parser;

AssignmentStatement::AssignmentStatement(BaseExpression* p_LeftExpression, BaseExpression* p_RightExpression) :
	m_LeftExpression(p_LeftExpression),
	m_RightExpression(p_RightExpression)
{

}

void AssignmentStatement::Generate()
{

}