#include "ArrayExpression.h"

#include "BaseExpression.h"

using namespace Parser;

ArrayExpression::ArrayExpression(BaseExpression* p_ArrayExpression, BaseExpression* p_IndexExpression) :
	m_ArrayExpression(p_ArrayExpression),
	m_IndexExpression(p_IndexExpression)
{

}

void ArrayExpression::Generate()
{

}