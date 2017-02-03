#pragma once

#include <Parser/VariableType.h>

namespace Parser
{
	class Identifier;

	class IExpression;
	typedef std::vector<IExpression*> ExpressionSeq;

	class ClassVariableType :
		public VariableType
	{
	public:
		ClassVariableType(Identifier* p_Type, ExpressionSeq* p_Arguments = nullptr);

	public:
		virtual void Generate() override;

	public:
		Identifier* m_Type;
		ExpressionSeq* m_Arguments;
	};
}