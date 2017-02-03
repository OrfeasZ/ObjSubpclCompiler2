#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class ProcedureHeader;
	class ProcedureBody;

	namespace ProcedureType
	{
		enum type
		{
			Standard,
			Abstract,
			Dynamic
		};
	}

	class Procedure
	{
	public:
		Procedure(ProcedureHeader* p_Header, ProcedureBody* p_Body = nullptr);

	public:
		inline void SetType(ProcedureType::type p_Type)
		{
			m_Type = p_Type;
		}

	public:
		ProcedureHeader* m_Header;
		ProcedureBody* m_Body;
		ProcedureType::type m_Type;
	};

	typedef std::vector<Procedure*> ProcedureSeq;
}