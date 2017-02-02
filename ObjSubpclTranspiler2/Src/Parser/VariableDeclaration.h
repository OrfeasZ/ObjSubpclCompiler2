#pragma once

#include "IParserType.h"

namespace Parser
{
	class VariableDeclaration :
		public IParserType
	{
	public:

	};

	typedef std::vector<VariableDeclaration*> ParameterSeq;
}