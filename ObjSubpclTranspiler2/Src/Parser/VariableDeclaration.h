#pragma once

#include "IParserType.h"

namespace Parser
{
	class VariableDeclaration :
		public IParserType
	{
	public:
		VariableDeclaration(IDSeq* p_IDs, VariableType* p_Type) :
			m_IDs(p_IDs),
			m_Type(p_Type)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		IDSeq* m_IDs;
		VariableType* m_Type;
	};

	typedef std::vector<VariableDeclaration*> VariableSeq;
}