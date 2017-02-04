#include "MemberCall.h"

#include <Parser/Identifier.h>

#include <Managers/CodeManager.h>

using namespace Parser;

MemberCall::MemberCall(BaseExpression* p_VariableExpression, Identifier* p_Name, ExpressionSeq* p_Arguments) :
	Call(p_Name, p_Arguments),
	m_VariableExpression(p_VariableExpression)
{
}

void MemberCall::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string MemberCall::ToString()
{
	std::string s_String = "";

	// TODO

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}