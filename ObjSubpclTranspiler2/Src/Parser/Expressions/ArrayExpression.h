#pragma once

#include "IExpression.h"

namespace Parser
{
	class IExpression;

	class ArrayExpression :
		public IExpression
	{
	public:
		ArrayExpression(IExpression* p_ArrayExpression, IExpression* p_IndexExpression);
		
	public:
		IExpression* m_ArrayExpression;
		IExpression* m_IndexExpression;
	};
}