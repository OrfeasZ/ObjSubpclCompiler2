#pragma once

#include "IExpression.h"

#include <sstream>

namespace Parser
{
	class Integer :
		public IExpression
	{
	public:
		Integer(const std::string& p_Value);

	public:
		virtual void Generate() override;

	public:
		int64_t m_Value;
	};
}