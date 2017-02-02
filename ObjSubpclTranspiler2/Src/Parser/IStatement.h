#pragma once

#include "IParserType.h"

namespace Parser
{
	class IStatement :
		public IParserType
	{
	public:

	};

	typedef std::vector<IStatement*> StatementSeq;
}