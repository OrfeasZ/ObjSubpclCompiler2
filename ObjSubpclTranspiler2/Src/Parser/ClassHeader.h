#pragma once

#include "IParserType.h"

namespace Parser
{
	class Identifier;

	class ClassHeader :
		public IParserType
	{
	public:
		ClassHeader(Identifier* p_Name, Identifier* p_Extends = nullptr);

	public:
		virtual void Generate() override;
		
	public:
		Identifier* m_Name;
		Identifier* m_Extends;
	};
}