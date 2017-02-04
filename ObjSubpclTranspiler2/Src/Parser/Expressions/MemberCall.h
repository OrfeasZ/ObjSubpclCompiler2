#pragma once

#include "Call.h"

namespace Parser
{
	class Identifier;

	class MemberCall :
		public Call
	{
	public:
		MemberCall(BaseExpression* p_VariableExpression, Identifier* p_Name, ExpressionSeq* p_Arguments = nullptr);

	public:
		virtual void Generate() override;
		virtual std::string ToString() override;

	public:
		BaseExpression* m_VariableExpression;
	};
}