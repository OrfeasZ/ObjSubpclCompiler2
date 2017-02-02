#pragma once

#include "IParserType.h"

namespace Parser
{
	class ProcedureBody :
		public IParserType
	{
	public:
		ProcedureBody(StatementSeq* p_Body, VariableSeq* p_Variables) :
			m_Body(p_Body),
			m_Variables(p_Variables)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		StatementSeq* m_Body;
		VariableSeq* m_Variables;
	};
}