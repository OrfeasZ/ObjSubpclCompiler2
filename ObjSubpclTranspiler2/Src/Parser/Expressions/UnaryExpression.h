#pragma once

#include "BaseExpression.h"

namespace Parser
{
	namespace UnaryExpressions
	{
		enum type
		{
			Not,
			Plus,
			Minus
		};
	}

	class UnaryExpression :
		public BaseExpression
	{
	public:
		UnaryExpression(BaseExpression* p_Expression, UnaryExpressions::type p_Type);

	public:
		virtual void Generate() override;
		virtual std::string ToString() override;

	public:
		BaseExpression* m_Expression;
		UnaryExpressions::type m_Type;
	};
}