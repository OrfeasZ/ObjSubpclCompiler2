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

#include "Real.h"

#include <Managers/CodeManager.h>

using namespace Parser;

Real::Real(const std::string& p_Left, const std::string& p_Right)
{
	std::stringstream s_Stream(p_Left + "." + p_Right);
	s_Stream >> m_Value;
}

void Real::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string Real::ToString()
{
	std::string s_String = std::to_string(m_Value);

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}