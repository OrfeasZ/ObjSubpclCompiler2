#pragma once

#include "IExpression.h"

#include <sstream>

namespace Parser
{
	class Real :
		public IExpression
	{
	public:
		Real::Real(const std::string& p_Left, const std::string& p_Right)
		{
			std::stringstream s_Stream(p_Left + "." + p_Right);
			s_Stream >> m_Value;
		}

	public:
		virtual void Generate() {}

	public:
		double m_Value;
	};
}