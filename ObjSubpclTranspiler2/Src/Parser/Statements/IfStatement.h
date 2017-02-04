#pragma once

#include "IStatement.h"

namespace Parser
{
	class BaseExpression;

	class IfStatement :
		public IStatement
	{
	public:
		IfStatement(BaseExpression* p_IfExpression, IStatement* p_ThenStatement, IStatement* p_ElseStatement = nullptr);

	public:
		virtual void Generate() override;

	public:
		BaseExpression* m_IfExpression;
		IStatement* m_ThenStatement;
		IStatement* m_ElseStatement;
	};
}