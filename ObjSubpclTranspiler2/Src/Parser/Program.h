#pragma once

#include "IParserType.h"

#include "Identifier.h"
#include "Body.h"

namespace Parser
{
	class Identifier;
	class Body;

	class Program :
		public IParserType
	{
	public:
		Program(Identifier* p_ID, Body* p_Body);

	public:
		virtual void Generate() override;

	public:
		Identifier* m_ID;
		Body* m_Body;
	};
}