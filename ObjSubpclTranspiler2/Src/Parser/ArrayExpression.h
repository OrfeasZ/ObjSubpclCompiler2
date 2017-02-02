#pragma once

#include "IExpression.h"

namespace Parser
{
	class ArrayExpression :
		public IExpression
	{
	public:
		ArrayExpression(IExpression* p_ArrayExpression, IExpression* p_IndexExpression) :
			m_ArrayExpression(p_ArrayExpression),
			m_IndexExpression(p_IndexExpression)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		IExpression* m_ArrayExpression;
		IExpression* m_IndexExpression;
	};
}