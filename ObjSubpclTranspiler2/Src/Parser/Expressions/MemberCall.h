#pragma once

#include "Call.h"

namespace Parser
{
	class Identifier;

	class MemberCall :
		public Call
	{
	public:
		MemberCall(IExpression* p_VariableExpression, Identifier* p_Name, ExpressionSeq* p_Arguments = nullptr);

	public:
		IExpression* m_VariableExpression;
	};
}