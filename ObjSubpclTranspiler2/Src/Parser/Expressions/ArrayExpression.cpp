#include "ArrayExpression.h"

#include "BaseExpression.h"

#include <Managers/CodeManager.h>

using namespace Parser;

ArrayExpression::ArrayExpression(BaseExpression* p_ArrayExpression, BaseExpression* p_IndexExpression) :
	m_ArrayExpression(p_ArrayExpression),
	m_IndexExpression(p_IndexExpression)
{

}

void ArrayExpression::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string ArrayExpression::ToString()
{
	m_ArrayExpression->SetParents(this);
	m_IndexExpression->SetParents(this);

	std::string s_String = m_ArrayExpression->ToString();

	s_String += "[";
	s_String += m_IndexExpression->ToString();
	s_String += "]";

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}

std::string ArrayExpression::GetType()
{
	return m_ArrayExpression->GetType();
}