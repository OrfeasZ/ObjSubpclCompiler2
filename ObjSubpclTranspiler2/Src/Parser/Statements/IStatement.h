#pragma once

#include <Misc/StdAfx.h>

#include <vector>

namespace Parser
{
	class IStatement
	{
	};

	class StatementSeq :
		public IStatement,
		public std::vector<IStatement*>
	{
	};
}