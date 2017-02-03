#pragma once

#include "IParserType.h"

namespace Parser
{
	class Procedure;
	typedef std::vector<Procedure*> ProcedureSeq;

	class ClassBody :
		public IParserType
	{
	public:
		ClassBody(Procedure* p_Constructor, ProcedureSeq* p_Procedures = nullptr);

	public:
		virtual void Generate() override;

	public:
		Procedure* m_Constructor;
		ProcedureSeq* m_Procedures;
	};
}