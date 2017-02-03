#pragma once

#include "IExpression.h"
#include <Parser/Statements/IStatement.h>

namespace Parser
{
	class Identifier;

	class Call :
		public IExpression,
		public IStatement
	{
	public:
		Call(Identifier* p_Name, ExpressionSeq* p_Arguments = nullptr);

	public:
		virtual void Generate() override;

	public:
		Identifier* m_Name;
		ExpressionSeq* m_Arguments;
	};

	typedef std::vector<Call*> CallSeq;
}
