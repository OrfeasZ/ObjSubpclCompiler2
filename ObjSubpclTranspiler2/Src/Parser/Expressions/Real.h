#pragma once

#include "BaseExpression.h"

#include <sstream>

namespace Parser
{
	class Real :
		public BaseExpression
	{
	public:
		Real::Real(const std::string& p_Left, const std::string& p_Right);

	public:
		virtual void Generate() override;
		virtual std::string ToString() override;

	public:
		double m_Value;
	};
}