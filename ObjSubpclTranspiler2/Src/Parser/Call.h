#pragma once

#include "IParserType.h"

namespace Parser
{
	class Call :
		public IParserType
	{
	public:

	};

	typedef std::vector<Call*> CallSeq;
}
