#pragma once

#include "IParserType.h"

namespace Parser
{
	namespace ProcedureType
	{
		enum type
		{
			Standard,
			Abstract,
			Dynamic
		};
	}

	class Procedure :
		public IParserType
	{
	public:
		Procedure(ProcedureHeader* p_Header, ProcedureBody* p_Body) :
			m_Header(p_Header),
			m_Body(p_Body),
			m_Type(ProcedureType::Standard)
		{

		}

	public:
		void SetType(ProcedureType::type p_Type)
		{
			m_Type = p_Type;
		}

		virtual void Generate()
		{

		}

	public:
		ProcedureHeader* m_Header;
		ProcedureBody* m_Body;
		ProcedureType::type m_Type;
	};

	typedef std::vector<Procedure*> ProcedureSeq;
}