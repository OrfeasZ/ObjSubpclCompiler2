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

#include "MemberValue.h"

#include <Parser/Identifier.h>

#include <Managers/CodeManager.h>
#include <Managers/ClassManager.h>

#include <Parser/ParserTree.h>

using namespace Parser;

MemberValue::MemberValue(BaseExpression* p_VariableExpression, Identifier* p_Member) :
	m_VariableExpression(p_VariableExpression),
	m_Member(p_Member)
{
}

void MemberValue::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string MemberValue::ToString()
{
	std::string s_String = "";

	m_VariableExpression->SetParents(this);
	
	auto s_MemberType = m_VariableExpression->GetType();
	auto s_MemberExpression = m_VariableExpression->ToString();
	auto s_ClassType = Managers::ClassManager::GetClass(s_MemberType);

	if (s_ClassType == nullptr)
		throw std::runtime_error("Tried access member variable '" + m_Member->m_Name + "' on a variable of unknown type.");

	auto s_TempParent = m_ParentClass;
	m_ParentClass = s_ClassType;

	bool s_Class = true;
	s_String += m_Member->GenerateMemberAccessor(this, s_MemberExpression);

	m_ParentClass = s_TempParent;

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}

std::string MemberValue::GetType()
{
	m_VariableExpression->SetParents(this);

	auto s_MemberType = m_VariableExpression->GetType();
	auto s_ClassType = Managers::ClassManager::GetClass(s_MemberType);

	if (s_ClassType == nullptr)
		return "";

	// Search the class members.
	VariableType* s_Type;
	if (s_ClassType->HasMember(m_Member->m_Name, s_Type))
		return VariableType::GetTypeFromVariableType(s_Type);

	return "";
}