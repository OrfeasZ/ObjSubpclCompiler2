#pragma once

#include "IStatement.h"

namespace Parser
{
	class ReturnStatement :
		public IStatement
	{
	public:
		ReturnStatement();

	public:
		virtual void Generate() override;
	};
}