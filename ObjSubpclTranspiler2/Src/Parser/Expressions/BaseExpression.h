#pragma once

#include <Misc/StdAfx.h>

#include <Parser/GeneratableChild.h>

namespace Parser
{
	class BaseExpression :
		public GeneratableChild
	{
	public:
		BaseExpression() :
			m_Enclosed(false)
		{
		}

	public:
		inline void SetEnclosed(bool p_Enclosed)
		{
			m_Enclosed = p_Enclosed;
		}

		virtual std::string ToString() = 0;

	public:
		bool m_Enclosed;
	};

	typedef std::vector<BaseExpression*> ExpressionSeq;
}