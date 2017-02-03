#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class IExpression
	{
	};

	typedef std::vector<IExpression*> ExpressionSeq;
}