#pragma once

#include <Parser/VariableType.h>

namespace Parser
{
	class Identifier;

	class BaseExpression;
	typedef std::vector<BaseExpression*> ExpressionSeq;

	class ClassVariableType :
		public VariableType
	{
	public:
		ClassVariableType(Identifier* p_ClassType, ExpressionSeq* p_Arguments = nullptr);

	public:
		virtual std::string ToString() override;

	public:
		Identifier* m_ClassType;
		ExpressionSeq* m_Arguments;
	};
}