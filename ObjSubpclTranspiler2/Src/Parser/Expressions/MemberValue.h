#pragma once

#include "IExpression.h"

namespace Parser
{
	class Identifier;

	class MemberValue :
		public IExpression
	{
	public:
		MemberValue(IExpression* p_VariableExpression, Identifier* p_Member);

	public:
		IExpression* m_VariableExpression;
		Identifier* m_Member;
	};
}