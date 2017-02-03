#pragma once

#include <Parser/IParserType.h>

namespace Parser
{
	class ClassHeader;

	class VariableDeclaration;
	typedef std::vector<VariableDeclaration*> VariableSeq;

	class ClassBody;

	class ClassDefinition :
		public IParserType
	{
	public:
		ClassDefinition(ClassHeader* p_Header, VariableSeq* p_Variables, ClassBody* p_Body);

	public:
		virtual void Generate() override;

	public:
		ClassHeader* m_Header;
		VariableSeq* m_Variables;
		ClassBody* m_Body;
	};

	typedef std::vector<ClassDefinition*> ClassSeq;
}