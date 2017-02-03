#pragma once

#include "IParserType.h"

namespace Parser
{
	class StatementSeq;

	class VariableDeclaration;
	typedef std::vector<VariableDeclaration*> VariableSeq;

	class Procedure;
	typedef std::vector<Procedure*> ProcedureSeq;

	class ClassDefinition;
	typedef std::vector<ClassDefinition*> ClassSeq;

	class Body :
		public IParserType
	{
	public:
		Body(StatementSeq* p_Body, VariableSeq* p_Variables = nullptr, ProcedureSeq* p_Procedures = nullptr, ClassSeq* p_Classes = nullptr);

	public:
		virtual void Generate() override;

	public:
		StatementSeq* m_Body;
		VariableSeq* m_Variables;
		ProcedureSeq* m_Procedures;
		ClassSeq* m_Classes;
	};
}