#pragma once

#include "IParserType.h"

namespace Parser
{
	class MemberCall :
		public IExpression,
		public IStatement
	{
	public:
		MemberCall(IExpression* p_VariableExpression, Identifier* p_Name, ExpressionSeq* p_Arguments) :
			m_VariableExpression(p_VariableExpression),
			m_Name(p_Name),
			m_Arguments(p_Arguments)
		{
		}

	public:
		virtual void Generate()
		{

		}

	public:
		IExpression* m_VariableExpression;
		Identifier* m_Name;
		ExpressionSeq* m_Arguments;
	};
}