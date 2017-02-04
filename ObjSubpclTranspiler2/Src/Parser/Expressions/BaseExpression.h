#pragma once

#include <Misc/StdAfx.h>

#include <Parser/GeneratableChild.h>

namespace Parser
{
	class BaseExpression :
		virtual public GeneratableChild
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
		virtual bool IsID() { return false; }

	public:
		bool m_Enclosed;
	};

	typedef std::vector<BaseExpression*> ExpressionSeq;
}