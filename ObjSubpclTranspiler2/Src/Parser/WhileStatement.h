#pragma once

#include "IStatement.h"

namespace Parser
{
	class WhileStatement:
		public IStatement
	{
	public:
		WhileStatement(IExpression* p_WhileExpression, IStatement* p_DoStatement) :
			m_WhileExpression(p_WhileExpression),
			m_DoStatement(p_DoStatement)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		IExpression* m_WhileExpression;
		IStatement* m_DoStatement;
	};
}