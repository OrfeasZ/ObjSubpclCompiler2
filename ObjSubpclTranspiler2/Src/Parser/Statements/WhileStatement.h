#pragma once

#include "IStatement.h"

namespace Parser
{
	class BaseExpression;

	class WhileStatement:
		public IStatement
	{
	public:
		WhileStatement(BaseExpression* p_WhileExpression, IStatement* p_DoStatement);

	public:
		virtual void Generate() override;

	public:
		BaseExpression* m_WhileExpression;
		IStatement* m_DoStatement;
	};
}