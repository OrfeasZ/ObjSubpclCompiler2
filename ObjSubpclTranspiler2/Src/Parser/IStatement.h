#pragma once

#include "IParserType.h"

#include <vector>

namespace Parser
{
	class IStatement :
		public IParserType
	{
	public:

	};

	class StatementSeq :
		public IStatement,
		public std::vector<IStatement*>
	{
	public:
		virtual void Generate() override {}
	};
}