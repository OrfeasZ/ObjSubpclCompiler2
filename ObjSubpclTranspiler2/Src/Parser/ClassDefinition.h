#pragma once

#include "IParserType.h"

namespace Parser
{
	class ClassDefinition :
		public IParserType
	{
	public:
		ClassDefinition(ClassHeader* p_Header, VariableSeq* p_Variables, ClassBody* p_Body) :
			m_Header(p_Header),
			m_Variables(p_Variables),
			m_Body(p_Body)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		ClassHeader* m_Header;
		VariableSeq* m_Variables;
		ClassBody* m_Body;
	};

	typedef std::vector<ClassDefinition*> ClassSeq;
}