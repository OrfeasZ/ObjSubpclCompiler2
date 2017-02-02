#pragma once

#include "IParserType.h"

namespace Parser
{
	class ClassDefinition :
		public IParserType
	{
	public:
		virtual void Generate()
		{

		}
	};

	typedef std::vector<ClassDefinition*> ClassSeq;
}