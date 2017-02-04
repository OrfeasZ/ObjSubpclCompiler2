#include "UnaryExpression.h"

using namespace Parser;

UnaryExpression::UnaryExpression(BaseExpression* p_Expression, UnaryExpressions::type p_Type) :
	m_Expression(p_Expression),
	m_Type(p_Type)
{
}

void UnaryExpression::Generate()
{

}