#pragma once

#include "IParserType.h"

namespace Parser
{
	class ClassBody :
		public IParserType
	{
	public:
		ClassBody(Procedure* p_Constructor, ProcedureSeq* p_Procedures) :
			m_Constructor(p_Constructor),
			m_Procedures(p_Procedures)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		Procedure* m_Constructor;
		ProcedureSeq* m_Procedures;
	};
}