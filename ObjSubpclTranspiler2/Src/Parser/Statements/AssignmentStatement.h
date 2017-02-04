#pragma once

#include "IStatement.h"

namespace Parser
{
	class BaseExpression;

	class AssignmentStatement :
		public IStatement
	{
	public:
		AssignmentStatement(BaseExpression* p_LeftExpression, BaseExpression* p_RightExpression);
		
	public:
		virtual void Generate() override;

	public:
		BaseExpression* m_LeftExpression;
		BaseExpression* m_RightExpression;
	};
}