#pragma once

#include "IStatement.h"

namespace Parser
{
	class IExpression;

	class IfStatement :
		public IStatement
	{
	public:
		IfStatement(IExpression* p_IfExpression, IStatement* p_ThenStatement, IStatement* p_ElseStatement = nullptr);

	public:
		IExpression* m_IfExpression;
		IStatement* m_ThenStatement;
		IStatement* m_ElseStatement;
	};
}