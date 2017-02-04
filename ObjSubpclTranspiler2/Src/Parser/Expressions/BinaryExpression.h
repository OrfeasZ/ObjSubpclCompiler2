#pragma once

#include "BaseExpression.h"

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
		public BaseExpression
	{
	public:
		BinaryExpression(BaseExpression* p_Left, BaseExpression* p_Right, BinaryExpressions::type p_Type);

	public:
		virtual void Generate() override;
		
	public:
		BaseExpression* m_Left;
		BaseExpression* m_Right;
		BinaryExpressions::type m_Type;
	};
}