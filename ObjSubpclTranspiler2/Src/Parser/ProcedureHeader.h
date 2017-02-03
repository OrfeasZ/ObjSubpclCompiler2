#pragma once

#include "IParserType.h"

namespace Parser
{
	class Identifier;

	class VariableDeclaration;
	typedef std::vector<VariableDeclaration*> VariableSeq;

	class ProcedureHeader :
		public IParserType
	{
	public:
		ProcedureHeader(Identifier* p_Name, VariableSeq* p_Parameters = nullptr);

	public:
		virtual void Generate() override;

	public:
		Identifier* m_Name;
		VariableSeq* m_Parameters;
	};
}