#pragma once

#include "IParserType.h"

namespace Parser
{
	class Identifier :
		public IParserType
	{
	public:

	};

	typedef std::vector<Identifier*> IDSeq;
}