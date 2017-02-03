#pragma once

#include "IParserType.h"

namespace Parser
{
	class Identifier;
	typedef std::vector<Identifier*> IDSeq;
	
	class VariableType;

	class VariableDeclaration :
		public IParserType
	{
	public:
		VariableDeclaration(IDSeq* p_IDs, VariableType* p_Type);

	public:
		virtual void Generate() override;

	public:
		IDSeq* m_IDs;
		VariableType* m_Type;
	};

	typedef std::vector<VariableDeclaration*> VariableSeq;
}