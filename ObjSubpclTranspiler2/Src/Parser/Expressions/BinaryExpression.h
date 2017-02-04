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
		BinaryExpression(IExpression* p_Left, IExpression* p_Right, BinaryExpressions::type p_Type);

	public:
		virtual void Generate() override;
		
	public:
		IExpression* m_Left;
		IExpression* m_Right;
		BinaryExpressions::type m_Type;
	};
}