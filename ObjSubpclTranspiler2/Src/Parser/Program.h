#pragma once

#include "IParserType.h"

#include "Identifier.h"
#include "Body.h"

namespace Parser
{
	class Program :
		public IParserType
	{
	public:
		Program(Identifier* p_ID, Body* p_Body) :
			m_ID(p_ID),
			m_Body(p_Body)
		{
		}

	public:
		virtual void Generate()
		{

		}

	public:
		Identifier* m_ID;
		Body* m_Body;
	};
}