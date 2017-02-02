#pragma once

#include "IParserType.h"

namespace Parser
{
	class Procedure :
		public IParserType
	{
	public:

	};

	typedef std::vector<Procedure*> ProcedureSeq;
}