#include "ClassManager.h"

#include <Parser/Class/ClassDefinition.h>
#include <Parser/Class/ClassHeader.h>
#include <Parser/Identifier.h>

using namespace Managers;

std::unordered_map<std::string, Parser::ClassDefinition*> ClassManager::m_Classes;

void ClassManager::RegisterClass(Parser::ClassDefinition* p_Class)
{
	m_Classes[p_Class->m_Header->m_Name->m_Name] = p_Class;
}

Parser::ClassDefinition* ClassManager::GetClass(const std::string& p_Name)
{
	auto s_Iterator = m_Classes.find(p_Name);

	if (s_Iterator == m_Classes.end())
		return nullptr;

	return s_Iterator->second;
}