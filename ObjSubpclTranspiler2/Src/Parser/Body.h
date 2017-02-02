#pragma once

#include "IParserType.h"

namespace Parser
{
	class Body :
		public IParserType
	{
	public:
		Body(StatementSeq* p_Body, VariableSeq* p_Variables = nullptr, ProcedureSeq* p_Procedures = nullptr, ClassSeq* p_Classes = nullptr) :
			m_Body(p_Body),
			m_Variables(p_Variables),
			m_Procedures(p_Procedures),
			m_Classes(p_Classes)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		StatementSeq* m_Body;
		VariableSeq* m_Variables;
		ProcedureSeq* m_Procedures;
		ClassSeq* m_Classes;
	};
}