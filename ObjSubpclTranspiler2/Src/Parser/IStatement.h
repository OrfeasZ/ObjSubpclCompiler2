#pragma once

#include "IParserType.h"

namespace Parser
{
	class IStatement :
		public IParserType
	{
	public:

	};

	class StatementSeq :
		public std::vector<IStatement*>,
		public IStatement
	{
	};
}