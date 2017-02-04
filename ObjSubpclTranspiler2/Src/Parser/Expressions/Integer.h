#pragma once

#include "BaseExpression.h"

#include <sstream>

namespace Parser
{
	class Integer :
		public BaseExpression
	{
	public:
		Integer(const std::string& p_Value);

	public:
		virtual void Generate() override;
		virtual std::string ToString() override;

	public:
		int64_t m_Value;
	};
}