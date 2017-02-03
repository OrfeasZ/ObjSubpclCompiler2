#pragma once

#include "IExpression.h"

#include <sstream>

namespace Parser
{
	class Real :
		public IExpression
	{
	public:
		Real::Real(const std::string& p_Left, const std::string& p_Right);

	public:
		virtual void Generate() override;

	public:
		double m_Value;
	};
}