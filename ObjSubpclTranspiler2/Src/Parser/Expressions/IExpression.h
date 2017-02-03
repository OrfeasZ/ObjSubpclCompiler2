#pragma once

#include <Parser/IParserType.h>

namespace Parser
{
	class IExpression :
		public IParserType
	{
	public:

	};

	typedef std::vector<IExpression*> ExpressionSeq;
}