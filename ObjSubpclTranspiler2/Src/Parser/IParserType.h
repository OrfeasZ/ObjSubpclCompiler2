#pragma once

#include <Misc/StdAfx.h>

#include <vector>

namespace Parser
{
	class IParserType
	{
	public:
		virtual void Generate() = 0;
	};
}