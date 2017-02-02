#pragma once

#include "IParserType.h"

namespace Parser
{
	class ClassHeader :
		public IParserType
	{
	public:
		ClassHeader(Identifier* p_Name, Identifier* p_Extends = nullptr) :
			m_Name,
			m_Extends
		{

		}

	public:
		virtual void Generate()
		{

		}
		
	public:
		Identifier* m_Name;
		Identifier* m_Extends;
	};
}