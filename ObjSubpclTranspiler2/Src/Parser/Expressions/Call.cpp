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

#include "Call.h"

#include <Parser/Identifier.h>
#include <Parser/Expressions/BaseExpression.h>

#include <Managers/CodeManager.h>

#include <Util/Utils.h>

using namespace Parser;

Call::Call(Identifier* p_Name, ExpressionSeq* p_Arguments) :
	m_Name(p_Name),
	m_Arguments(p_Arguments)
{

}

void Call::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string Call::ToString()
{
	std::string s_String = "";

	// Special handling for print calls.
	if (m_Name->m_Name == "PrintOut")
	{
		// Make sure we have exactly one argument.
		if (!m_Arguments || m_Arguments->size() != 1)
			throw std::runtime_error("PrintOut calls must have exactly 1 argument.");

		(*m_Arguments)[0]->SetParents(this);
		s_String = m_Name->m_Name + "(" + (*m_Arguments)[0]->ToString() + ")";
	}
	else
	{
		bool s_Class = false;
		s_String = m_Name->GenerateCallAccessor(this, "th", s_Class);

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

		// If this is a class call add th as the first argument.
		if (s_Class)
			s_Arguments.insert(s_Arguments.begin(), "th");

		s_String += "(" + Util::Utils::Join(s_Arguments, ", ") + ")";
	}

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}