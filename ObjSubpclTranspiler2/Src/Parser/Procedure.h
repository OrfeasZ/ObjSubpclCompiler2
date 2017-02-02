#pragma once

#include "IParserType.h"

namespace Parser
{
	class Procedure :
		public IParserType
	{
	public:
		virtual void Generate()
		{

		}
	};

	typedef std::vector<Procedure*> ProcedureSeq;
}