#include "BinaryExpression.h"

#include <Managers/CodeManager.h>

using namespace Parser;

BinaryExpression::BinaryExpression(BaseExpression* p_Left, BaseExpression* p_Right, BinaryExpressions::type p_Type) :
	m_Left(p_Left),
	m_Right(p_Right),
	m_Type(p_Type)
{
}

void BinaryExpression::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string BinaryExpression::ToString()
{
	m_Left->SetParents(this);
	m_Right->SetParents(this);

	std::string s_String = "";

	s_String += m_Left->ToString();

	switch (m_Type)
	{
	case BinaryExpressions::Plus:
		s_String += " + ";
		break;

	case BinaryExpressions::Minus:
		s_String += " - ";
		break;

	case BinaryExpressions::Multiply:
		s_String += " * ";
		break;

	case BinaryExpressions::Divide:
		s_String += " / ";
		break;

	case BinaryExpressions::Div:
		// TODO: Do we need to handle div differently?
		s_String += " / ";
		break;

	case BinaryExpressions::Mod:
		s_String += " % ";
		break;

	case BinaryExpressions::Or:
		s_String += " || ";
		break;

	case BinaryExpressions::And:
		s_String += " && ";
		break;

	case BinaryExpressions::Equal:
		s_String += " == ";
		break;

	case BinaryExpressions::NotEqual:
		s_String += " != ";
		break;

	case BinaryExpressions::LessThan:
		s_String += " < ";
		break;

	case BinaryExpressions::LessThanEqual:
		s_String += " <= ";
		break;

	case BinaryExpressions::GreaterThan:
		s_String += " > ";
		break;

	case BinaryExpressions::GreaterThanEqual:
		s_String += " >= ";
		break;
	}

	s_String += m_Right->ToString();

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}