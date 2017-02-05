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

#include "ProcedureHeader.h"

#include <Parser/Identifier.h>
#include <Parser/VariableDeclaration.h>
#include <Parser/Identifier.h>
#include <Parser/VariableType.h>

using namespace Parser;

ProcedureHeader::ProcedureHeader(Identifier* p_Name, VariableSeq* p_Parameters) :
	m_Name(p_Name),
	m_Parameters(p_Parameters)
{

}

std::vector<std::string> ProcedureHeader::GetParameters()
{
	std::vector<std::string> s_Parameters;

	if (!m_Parameters)
		return s_Parameters;

	for (auto s_ParameterGroup : *m_Parameters)
	{
		for (auto s_ID : *s_ParameterGroup->m_IDs)
		{
			std::string s_Parameter = s_ParameterGroup->m_Type->ToString();

			if (s_ParameterGroup->m_Type->m_Type == VariableTypes::Class || s_ParameterGroup->m_Type->m_Type == VariableTypes::ClassPointer)
				s_Parameter += "*";
			else if (s_ParameterGroup->m_Type->m_Type == VariableTypes::Array)
				s_Parameter += "**";

			s_Parameter += " " + s_ID->m_Name;
			s_Parameters.push_back(s_Parameter);
		}
	}

	return s_Parameters;
}