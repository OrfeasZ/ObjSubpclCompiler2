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

#include "UnaryExpression.h"

#include <Managers/CodeManager.h>

using namespace Parser;

UnaryExpression::UnaryExpression(BaseExpression* p_Expression, UnaryExpressions::type p_Type) :
	m_Expression(p_Expression),
	m_Type(p_Type)
{
}

void UnaryExpression::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string UnaryExpression::ToString()
{
	m_Expression->SetParents(this);

	std::string s_String = "";

	switch (m_Type)
	{
	case UnaryExpressions::Not:
		s_String += "!";
		break;

	case UnaryExpressions::Plus:
		s_String += "+";
		break;

	case UnaryExpressions::Minus:
		s_String += "-";
		break;
	}

	s_String += m_Expression->ToString();

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}