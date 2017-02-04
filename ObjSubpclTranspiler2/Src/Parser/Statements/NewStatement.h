#pragma once

#include "IStatement.h"

namespace Parser
{
	class Identifier;

	class BaseExpression;
	typedef std::vector<BaseExpression*> ExpressionSeq;

	class NewStatement :
		public IStatement
	{
	public:
		NewStatement(BaseExpression* p_LeftExpression, Identifier* p_ClassName, ExpressionSeq* p_Arguments = nullptr);

	public:
		virtual void Generate() override;

	public:
		BaseExpression* m_LeftExpression;
		Identifier* m_ClassName;
		ExpressionSeq* m_Arguments;
	};
}