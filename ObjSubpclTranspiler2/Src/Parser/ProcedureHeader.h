#pragma once

#include "IParserType.h"

namespace Parser
{
	class ProcedureHeader :
		public IParserType
	{
	public:
		ProcedureHeader(Identifier* p_Name, VariableSeq* p_Parameters) :
			m_Name(p_Name),
			m_Parameters(p_Parameters)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		Identifier* m_Name;
		VariableSeq* m_Parameters;
	};
}