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

#include "BinaryExpression.h"

#include <Managers/CodeManager.h>

using namespace Parser;

BinaryExpression::BinaryExpression(BaseExpression* p_Left, BaseExpression* p_Right, BinaryExpressions::type p_Type) :
	m_Left(p_Left),
	m_Right(p_Right),
	m_Type(p_Type)
{
}

void BinaryExpression::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string BinaryExpression::ToString()
{
	m_Left->SetParents(this);
	m_Right->SetParents(this);

	std::string s_String = "";

	// Special case for integer division.
	if (m_Type == BinaryExpressions::Div)
		s_String += "(long) (";

	s_String += m_Left->ToString();

	switch (m_Type)
	{
	case BinaryExpressions::Plus:
		s_String += " + ";
		break;

	case BinaryExpressions::Minus:
		s_String += " - ";
		break;

	case BinaryExpressions::Multiply:
		s_String += " * ";
		break;

	case BinaryExpressions::Divide:
		s_String += " / ";
		break;

	case BinaryExpressions::Div:
		s_String += ") / (long) (";
		break;

	case BinaryExpressions::Mod:
		s_String += " % ";
		break;

	case BinaryExpressions::Or:
		s_String += " || ";
		break;

	case BinaryExpressions::And:
		s_String += " && ";
		break;

	case BinaryExpressions::Equal:
		s_String += " == ";
		break;

	case BinaryExpressions::NotEqual:
		s_String += " != ";
		break;

	case BinaryExpressions::LessThan:
		s_String += " < ";
		break;

	case BinaryExpressions::LessThanEqual:
		s_String += " <= ";
		break;

	case BinaryExpressions::GreaterThan:
		s_String += " > ";
		break;

	case BinaryExpressions::GreaterThanEqual:
		s_String += " >= ";
		break;
	}

	s_String += m_Right->ToString();

	// Special case for integer division.
	if (m_Type == BinaryExpressions::Div)
		s_String += ")";

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}