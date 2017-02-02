#pragma once

#include "IStatement.h"

namespace Parser
{
	class IfStatement :
		public IStatement
	{
	public:
		IfStatement(IExpression* p_IfExpression, IStatement* p_ThenStatement, IStatement* p_ElseStatement = nullptr) :
			m_IfExpression(p_IfExpression),
			m_ThenStatement(p_ThenStatement),
			m_ElseStatement(p_ElseStatement)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		IExpression* m_IfExpression;
		IStatement* m_ThenStatement;
		IStatement* m_ElseStatement;
	};
}