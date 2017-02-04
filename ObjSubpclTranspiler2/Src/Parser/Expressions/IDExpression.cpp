#include "IDExpression.h"

#include <Managers/CodeManager.h>

#include <Parser/ParserTree.h>

using namespace Parser;

IDExpression::IDExpression(Identifier* p_ID) :
	m_ID(p_ID)
{

}

void IDExpression::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string IDExpression::ToString()
{
	std::string s_String = m_ID->GenerateMemberAccessor(this, "th");

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}

std::string IDExpression::GetType()
{
	VariableType* s_Type = nullptr;

	if (m_ParentVariables && m_ParentVariables->HasVariable(m_ID->m_Name, s_Type))
		return VariableType::GetTypeFromVariableType(s_Type);

	// Search our parameters.
	if (m_ParentParameters && m_ParentParameters->HasVariable(m_ID->m_Name, s_Type))
		return VariableType::GetTypeFromVariableType(s_Type);

	// Search the class members.
	if (m_ParentClass && m_ParentClass->HasMember(m_ID->m_Name, s_Type))
		return VariableType::GetTypeFromVariableType(s_Type);

	// Search the global variables.
	auto s_ProgramBody = Parser::ParserTree::GetProgram()->m_Body;
	if (s_ProgramBody && s_ProgramBody->m_Variables && s_ProgramBody->m_Variables->HasVariable(m_ID->m_Name, s_Type))
		return VariableType::GetTypeFromVariableType(s_Type);

	return "";
}