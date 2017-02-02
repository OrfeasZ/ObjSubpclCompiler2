#pragma once

#include "IParserType.h"

#include <sstream>

namespace Parser
{
	class Integer :
		public IExpression
	{
	public:
		Integer(const std::string& p_Value)
		{
			std::stringstream s_Stream(p_Value);
			s_Stream >> m_Value;
		}

	public:
		virtual void Generate() {}

	public:
		int64_t m_Value;
	};
}