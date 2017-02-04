#pragma once

#include <Misc/StdAfx.h>

#include <Parser/GeneratableChild.h>

namespace Parser
{
	class IExpression :
		public GeneratableChild
	{
	};

	typedef std::vector<IExpression*> ExpressionSeq;
}