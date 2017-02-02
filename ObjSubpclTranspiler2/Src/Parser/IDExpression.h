#pragma once

#include "IParserType.h"

namespace Parser
{
	class IDExpression :
		public IParserType
	{
	public:
		IDExpression(Identifier* p_ID) :
			m_ID(p_ID)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		Identifier* m_ID;
	};
}