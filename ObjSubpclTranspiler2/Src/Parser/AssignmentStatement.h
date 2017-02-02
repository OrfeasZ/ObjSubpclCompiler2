#pragma once

#include "IStatement.h"

namespace Parser
{
	class AssignmentStatement :
		public IStatement
	{
	public:
		AssignmentStatement(IExpression* p_LeftExpression, IExpression* p_RightExpression) :
			m_LeftExpression(p_LeftExpression),
			m_RightExpression(p_RightExpression)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		IExpression* m_LeftExpression;
		IExpression* m_RightExpression;
	};
}