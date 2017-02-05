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