#include "UnaryExpression.h"

#include <Managers/CodeManager.h>

using namespace Parser;

UnaryExpression::UnaryExpression(BaseExpression* p_Expression, UnaryExpressions::type p_Type) :
	m_Expression(p_Expression),
	m_Type(p_Type)
{
}

void UnaryExpression::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string UnaryExpression::ToString()
{
	m_Expression->SetParents(this);

	std::string s_String = "";

	switch (m_Type)
	{
	case UnaryExpressions::Not:
		s_String += "!";
		break;

	case UnaryExpressions::Plus:
		s_String += "+";
		break;

	case UnaryExpressions::Minus:
		s_String += "-";
		break;
	}

	s_String += m_Expression->ToString();

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}