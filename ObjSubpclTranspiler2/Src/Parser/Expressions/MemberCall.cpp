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

#include "MemberCall.h"

#include <Parser/Identifier.h>

#include <Managers/CodeManager.h>
#include <Managers/ClassManager.h>

#include <Parser/Expressions/IDExpression.h>
#include <Parser/Class/ClassDefinition.h>
#include <Parser/Class/ClassHeader.h>

#include <Util/Utils.h>

using namespace Parser;

MemberCall::MemberCall(BaseExpression* p_VariableExpression, Identifier* p_Name, ExpressionSeq* p_Arguments) :
	Call(p_Name, p_Arguments),
	m_VariableExpression(p_VariableExpression)
{
}

void MemberCall::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string MemberCall::ToString()
{
	std::string s_String = "";

	// Is this a super call?
	bool s_SuperCall = false;
	if (m_VariableExpression->IsID())
	{
		auto s_Expression = (IDExpression*) m_VariableExpression;
		s_SuperCall = s_Expression->m_ID->m_Name == "super";
	}
	
	m_VariableExpression->SetParents(this);

	if (!s_SuperCall || m_ParentClass == nullptr)
	{
		auto s_MemberType = m_VariableExpression->GetType();
		auto s_MemberExpression = m_VariableExpression->ToString();
		auto s_ClassType = Managers::ClassManager::GetClass(s_MemberType);

		if (s_ClassType == nullptr)
			throw std::runtime_error("Tried calling function '" + m_Name->m_Name + "' on a variable of unknown type.");

		auto s_TempParent = m_ParentClass;
		m_ParentClass = s_ClassType;

		bool s_Class = true;
		s_String += m_Name->GenerateCallAccessor(this, s_MemberExpression, s_Class);

		m_ParentClass = s_TempParent;

		std::vector<std::string> s_Arguments;

		// Serialize our arguments.
		if (m_Arguments)
		{
			for (auto s_Expression : *m_Arguments)
			{
				s_Expression->SetParents(this);
				s_Arguments.push_back(s_Expression->ToString());
			}
		}

		// This is a class call so add th as the first argument.
		s_Arguments.insert(s_Arguments.begin(), s_MemberExpression);

		s_String += "(" + Util::Utils::Join(s_Arguments, ", ") + ")";
	}
	else
	{
		// Special handling for super calls.
		if (m_ParentClass->m_Header->m_Extends == nullptr)
			throw std::runtime_error("Trying to call function '" + m_Name->m_Name + "' on non-existent base class.");

		if (m_Name->m_Name == "ctor")
		{
			// We skip constructor calls as those are handled by the class definition constructo generator.
			return "";
		}
		else
		{
			auto s_TempParent = m_ParentClass;
			m_ParentClass = Managers::ClassManager::GetClass(m_ParentClass->m_Header->m_Extends->m_Name);

			bool s_Class = true;
			s_String += m_Name->GenerateCallAccessor(this, "th", s_Class);

			m_ParentClass = s_TempParent;

			std::vector<std::string> s_Arguments;

			// Serialize our arguments.
			if (m_Arguments)
			{
				for (auto s_Expression : *m_Arguments)
				{
					s_Expression->SetParents(this);
					s_Arguments.push_back(s_Expression->ToString());
				}
			}

			// This is a class call so add th as the first argument.
			s_Arguments.insert(s_Arguments.begin(), "th");

			s_String += "(" + Util::Utils::Join(s_Arguments, ", ") + ")";
		}
	}

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}