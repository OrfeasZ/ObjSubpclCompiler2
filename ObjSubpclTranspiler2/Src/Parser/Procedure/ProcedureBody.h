#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class StatementSeq;
	class VariableSeq;

	class ProcedureBody
	{
	public:
		ProcedureBody(StatementSeq* p_Body, VariableSeq* p_Variables = nullptr);

	public:
		StatementSeq* m_Body;
		VariableSeq* m_Variables;
	};
}