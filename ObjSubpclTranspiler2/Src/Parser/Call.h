#pragma once

#include "IExpression.h"
#include "IStatement.h"

namespace Parser
{
	class Call :
		public IExpression,
		public IStatement
	{
	public:
		Call(Identifier* p_Name, ExpressionSeq* p_Arguments) :
			m_Name(p_Name),
			m_Arguments(p_Arguments)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		Identifier* m_Name;
		ExpressionSeq* m_Arguments;
	};

	typedef std::vector<Call*> CallSeq;
}
