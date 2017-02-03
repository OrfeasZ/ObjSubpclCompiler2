#pragma once

#include "IStatement.h"

namespace Parser
{
	class IExpression;

	class WhileStatement:
		public IStatement
	{
	public:
		WhileStatement(IExpression* p_WhileExpression, IStatement* p_DoStatement);

	public:
		virtual void Generate() override;

	public:
		IExpression* m_WhileExpression;
		IStatement* m_DoStatement;
	};
}