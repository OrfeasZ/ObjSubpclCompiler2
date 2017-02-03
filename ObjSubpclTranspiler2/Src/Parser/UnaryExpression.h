#pragma once

#include "IExpression.h"

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
		public IExpression
	{
	public:
		UnaryExpression(IExpression* p_Expression, UnaryExpressions::type p_Type);

	public:
		virtual void Generate() override;

	public:
		IExpression* m_Expression;
		UnaryExpressions::type m_Type;
	};
}