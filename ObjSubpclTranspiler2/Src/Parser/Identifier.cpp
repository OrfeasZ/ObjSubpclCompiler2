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

#include "Identifier.h"

#include <Parser/ParserTree.h>

using namespace Parser;

Identifier::Identifier(const std::string& p_Name) :
	m_Name(p_Name)
{
}

std::string Identifier::GenerateMemberAccessor(GeneratableChild* p_ChildData, const std::string& p_ClassName)
{
	VariableType* s_Type = nullptr;

	// Our search priority is: block -> params -> class -> global.
	// Search the local variables block.
	if (p_ChildData->m_ParentVariables && p_ChildData->m_ParentVariables->HasVariable(m_Name, s_Type))
		return m_Name;

	// Search our parameters.
	if (p_ChildData->m_ParentParameters && p_ChildData->m_ParentParameters->HasVariable(m_Name, s_Type))
		return m_Name;

	// Search the class members.
	if (p_ChildData->m_ParentClass && p_ChildData->m_ParentClass->HasMember(m_Name, s_Type))
		return p_ClassName + "->" + m_Name;

	// Search the global variables.
	auto s_ProgramBody = Parser::ParserTree::GetProgram()->m_Body;
	if (s_ProgramBody && s_ProgramBody->m_Variables && s_ProgramBody->m_Variables->HasVariable(m_Name, s_Type))
		return m_Name;

	throw std::runtime_error("Use of undefined variable '" + m_Name + "'.");
}

std::string Identifier::GenerateCallAccessor(GeneratableChild* p_ChildData, const std::string& p_ClassName, bool& p_Class)
{
	bool s_ClassOnly = p_Class;

	// Our search priority is: class -> parents -> global.
	if (p_ChildData->m_ParentClass)
	{
		p_Class = true;

		std::string s_MethodName;
		if (p_ChildData->m_ParentClass->HasMethod(m_Name, s_MethodName, true))
			return s_MethodName;
		
		if (p_ChildData->m_ParentClass->HasVirtualMethod(s_MethodName))
			return "((struct " + p_ChildData->m_ParentClass->m_Header->m_Name->m_Name + "_vtbl_t*) " + p_ClassName + "->vtbl)->" + m_Name;
	}

	if (s_ClassOnly)
		throw std::runtime_error("Use of undefined method '" + m_Name + "'.");

	p_Class = false;

	auto s_ProgramBody = Parser::ParserTree::GetProgram()->m_Body;

	if (s_ProgramBody && s_ProgramBody->m_Procedures)
		for (auto s_Procedure : *s_ProgramBody->m_Procedures)
			if (s_Procedure->m_Header->m_Name->m_Name == m_Name)
				return m_Name;

	throw std::runtime_error("Use of undefined method '" + m_Name + "'.");
}