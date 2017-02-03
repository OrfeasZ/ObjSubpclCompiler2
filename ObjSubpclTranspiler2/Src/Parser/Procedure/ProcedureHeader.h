#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class Identifier;

	class VariableDeclaration;
	typedef std::vector<VariableDeclaration*> VariableSeq;

	class ProcedureHeader
	{
	public:
		ProcedureHeader(Identifier* p_Name, VariableSeq* p_Parameters = nullptr);

	public:
		Identifier* m_Name;
		VariableSeq* m_Parameters;
	};
}