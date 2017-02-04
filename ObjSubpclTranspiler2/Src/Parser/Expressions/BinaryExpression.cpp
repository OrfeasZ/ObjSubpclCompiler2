#include "BinaryExpression.h"

using namespace Parser;

BinaryExpression::BinaryExpression(IExpression* p_Left, IExpression* p_Right, BinaryExpressions::type p_Type) :
	m_Left(p_Left),
	m_Right(p_Right),
	m_Type(p_Type)
{
}

void BinaryExpression::Generate()
{

}