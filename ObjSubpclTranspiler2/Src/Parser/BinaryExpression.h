#pragma once

#include "IExpression.h"

namespace Parser
{
	namespace BinaryExpressions
	{
		enum type
		{
			Plus,
			Minus,
			Multiply,
			Divide,
			Div,
			Mod,
			Or,
			And,
			Equal,
			NotEqual,
			LessThan,
			LessThanEqual,
			GreaterThan,
			GreaterThanEqual
		};
	}

	class BinaryExpression :
		public IExpression
	{
	public:
		virtual void Generate()
		{

		}
	};
}