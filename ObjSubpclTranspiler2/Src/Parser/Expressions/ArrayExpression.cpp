#include "ArrayExpression.h"

#include "IExpression.h"

using namespace Parser;

ArrayExpression::ArrayExpression(IExpression* p_ArrayExpression, IExpression* p_IndexExpression) :
	m_ArrayExpression(p_ArrayExpression),
	m_IndexExpression(p_IndexExpression)
{

}