#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class Identifier;
	typedef std::vector<Identifier*> IDSeq;
	
	class VariableType;

	class VariableDeclaration
	{
	public:
		VariableDeclaration(IDSeq* p_IDs, VariableType* p_Type);

	public:
		IDSeq* m_IDs;
		VariableType* m_Type;
	};

	typedef std::vector<VariableDeclaration*> VariableSeq;
}