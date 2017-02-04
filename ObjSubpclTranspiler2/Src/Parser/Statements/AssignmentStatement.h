#pragma once

#include "IStatement.h"

namespace Parser
{
	class IExpression;

	class AssignmentStatement :
		public IStatement
	{
	public:
		AssignmentStatement(IExpression* p_LeftExpression, IExpression* p_RightExpression);
		
	public:
		virtual void Generate() override;

	public:
		IExpression* m_LeftExpression;
		IExpression* m_RightExpression;
	};
}