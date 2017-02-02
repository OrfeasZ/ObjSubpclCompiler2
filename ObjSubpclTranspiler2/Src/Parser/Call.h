#pragma once

#include "IExpression.h"
#include "IStatement.h"

namespace Parser
{
	class Call :
		public IExpression,
		public IStatement
	{
	public:
		virtual void Generate()
		{

		}
	};

	typedef std::vector<Call*> CallSeq;
}
