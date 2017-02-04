#pragma once

#include "BaseExpression.h"

namespace Parser
{
	class Identifier;

	class IDExpression :
		public BaseExpression
	{
	public:
		IDExpression(Identifier* p_ID);

	public:
		virtual void Generate() override;

	public:
		Identifier* m_ID;
	};
}