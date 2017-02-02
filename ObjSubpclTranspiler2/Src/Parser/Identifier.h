#pragma once

#include "IParserType.h"

namespace Parser
{
	class Identifier :
		public IParserType
	{
	public:
		Identifier(const std::string& p_Name) :
			m_Name(p_Name)
		{
		}

	public:
		virtual void Generate()
		{

		}
	public:
		std::string m_Name;
	};

	typedef std::vector<Identifier*> IDSeq;
}