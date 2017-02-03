#pragma once

#include "IParserType.h"

namespace Parser
{
	class StatementSeq;

	class VariableDeclaration;
	typedef std::vector<VariableDeclaration*> VariableSeq;

	class ProcedureBody :
		public IParserType
	{
	public:
		ProcedureBody(StatementSeq* p_Body, VariableSeq* p_Variables = nullptr);

	public:
		virtual void Generate() override;

	public:
		StatementSeq* m_Body;
		VariableSeq* m_Variables;
	};
}