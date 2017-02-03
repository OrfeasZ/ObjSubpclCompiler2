#pragma once

#include "IExpression.h"

namespace Parser
{
	class Identifier;

	class IDExpression :
		public IExpression
	{
	public:
		IDExpression(Identifier* p_ID);

	public:
		virtual void Generate() override;

	public:
		Identifier* m_ID;
	};
}