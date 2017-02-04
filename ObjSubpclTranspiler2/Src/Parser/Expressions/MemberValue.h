#pragma once

#include "BaseExpression.h"

namespace Parser
{
	class Identifier;

	class MemberValue :
		public BaseExpression
	{
	public:
		MemberValue(BaseExpression* p_VariableExpression, Identifier* p_Member);

	public:
		virtual void Generate() override;

	public:
		BaseExpression* m_VariableExpression;
		Identifier* m_Member;
	};
}