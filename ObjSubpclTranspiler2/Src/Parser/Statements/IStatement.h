#pragma once

#include <Misc/StdAfx.h>

#include <vector>

#include <Parser/GeneratableChild.h>

namespace Parser
{
	class IStatement : 
		public GeneratableChild
	{
	};

	class StatementSeq :
		public IStatement,
		public std::vector<IStatement*>
	{
	public:
		virtual void Generate() override {}
	};
}