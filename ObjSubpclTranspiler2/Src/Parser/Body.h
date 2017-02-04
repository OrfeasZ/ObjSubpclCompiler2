#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class StatementSeq;
	class VariableSeq;

	class Procedure;
	typedef std::vector<Procedure*> ProcedureSeq;

	class ClassDefinition;
	typedef std::vector<ClassDefinition*> ClassSeq;

	class Body
	{
	public:
		Body(StatementSeq* p_Body, VariableSeq* p_Variables = nullptr, ProcedureSeq* p_Procedures = nullptr, ClassSeq* p_Classes = nullptr);

	public:
		StatementSeq* m_Body;
		VariableSeq* m_Variables;
		ProcedureSeq* m_Procedures;
		ClassSeq* m_Classes;
	};
}