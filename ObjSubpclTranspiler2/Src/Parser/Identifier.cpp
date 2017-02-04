#include "Identifier.h"

#include <Parser/ParserTree.h>

using namespace Parser;

Identifier::Identifier(const std::string& p_Name) :
	m_Name(p_Name)
{
}

std::string Identifier::GenerateAccessor(GeneratableChild* p_ChildData, bool p_Call)
{
	if (p_Call)
		return GenerateCallAccessor(p_ChildData);

	return GenerateMemberAccessor(p_ChildData);
}

std::string Identifier::GenerateMemberAccessor(GeneratableChild* p_ChildData)
{
	// Our search priority is: block -> params -> class -> global.
	// Search the local variables block.
	if (p_ChildData->m_ParentVariables && p_ChildData->m_ParentVariables->HasVariable(m_Name))
		return m_Name;

	// Search our parameters.
	if (p_ChildData->m_ParentParameters && p_ChildData->m_ParentParameters->HasVariable(m_Name))
		return m_Name;

	// Search the class members.
	if (p_ChildData->m_ParentClass && p_ChildData->m_ParentClass->HasMember(m_Name))
		return "th->" + m_Name;

	// Search the global variables.
	auto s_ProgramBody = Parser::ParserTree::GetProgram()->m_Body;
	if (s_ProgramBody && s_ProgramBody->m_Variables && s_ProgramBody->m_Variables->HasVariable(m_Name))
		return m_Name;

	throw std::exception(("Use of undefined variable '" + m_Name + "'.").c_str());
}

std::string Identifier::GenerateCallAccessor(GeneratableChild* p_ChildData)
{
	return "";
}