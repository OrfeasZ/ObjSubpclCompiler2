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
		IExpression* m_Expression;
		UnaryExpressions::type m_Type;
	};
}