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
		virtual void Generate()
		{

		}
	};
}