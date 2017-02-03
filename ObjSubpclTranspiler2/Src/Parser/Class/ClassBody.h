#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class Procedure;
	typedef std::vector<Procedure*> ProcedureSeq;

	class ClassBody
	{
	public:
		ClassBody(Procedure* p_Constructor, ProcedureSeq* p_Procedures = nullptr);
		
	public:
		Procedure* m_Constructor;
		ProcedureSeq* m_Procedures;
	};
}