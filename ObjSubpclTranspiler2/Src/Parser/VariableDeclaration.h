#pragma once

#include "IParserType.h"

namespace Parser
{
	class VariableDeclaration :
		public IParserType
	{
	public:
		virtual void Generate()
		{

		}
	};

	typedef std::vector<VariableDeclaration*> VariableSeq;
}