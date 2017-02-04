#pragma once

#include <Misc/StdAfx.h>

#include <Parser/GeneratableChild.h>

namespace Parser
{
	class BaseExpression :
		public GeneratableChild
	{
	public:
		inline void SetEnclosed(bool p_Enclosed)
		{
			m_Enclosed = p_Enclosed;
		}

	public:
		bool m_Enclosed;
	};

	typedef std::vector<BaseExpression*> ExpressionSeq;
}