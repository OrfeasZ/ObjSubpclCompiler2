/*
 * ObjSubpclTranspiler
 * Copyright (c) 2016 - 2017, Orfeas Zafeiris
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright holders reserve the right to release and distribute this 
 * program under different license terms.
 */

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