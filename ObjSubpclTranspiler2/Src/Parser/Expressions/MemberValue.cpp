#include "MemberValue.h"

#include <Parser/Identifier.h>

#include <Managers/CodeManager.h>

using namespace Parser;

MemberValue::MemberValue(BaseExpression* p_VariableExpression, Identifier* p_Member) :
	m_VariableExpression(p_VariableExpression),
	m_Member(p_Member)
{
}

void MemberValue::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string MemberValue::ToString()
{
	std::string s_String = "";

	// TODO

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}