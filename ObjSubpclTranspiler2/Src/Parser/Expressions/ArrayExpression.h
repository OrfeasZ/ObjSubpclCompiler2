#pragma once

#include "BaseExpression.h"

namespace Parser
{
	class BaseExpression;

	class ArrayExpression :
		public BaseExpression
	{
	public:
		ArrayExpression(BaseExpression* p_ArrayExpression, BaseExpression* p_IndexExpression);

	public:
		virtual void Generate() override;
		virtual std::string ToString() override;
		
	public:
		BaseExpression* m_ArrayExpression;
		BaseExpression* m_IndexExpression;
	};
}