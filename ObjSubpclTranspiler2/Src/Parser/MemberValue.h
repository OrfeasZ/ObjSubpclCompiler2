#pragma once

#include "IParserType.h"

namespace Parser
{
	class MemberValue :
		public IParserType
	{
	public:
		MemberValue(IExpression* p_VariableExpression, Identifier* p_Member) :
			m_VariableExpression(p_VariableExpression),
			m_Member(p_Member)
		{
		}

	public:
		virtual void Generate()
		{

		}

	public:
		IExpression* m_VariableExpression;
		Identifier* m_Member;
	};
}