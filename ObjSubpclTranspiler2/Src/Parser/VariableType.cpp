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

#include "VariableType.h"

#include "ArrayVariableType.h"

#include <Parser/Class/ClassVariablePointerType.h>
#include <Parser/Class/ClassVariableType.h>
#include <Parser/Identifier.h>

using namespace Parser;

VariableType::VariableType(VariableTypes::type p_Type) :
	m_Type(p_Type)
{

}

std::string VariableType::ToString()
{
	switch (m_Type)
	{
	case VariableTypes::Integer:
		return "long";

	case VariableTypes::Real:
		return "double";

	default:
		return "";
	}
}

std::string VariableType::GetTypeFromVariableType(VariableType* p_Type)
{
	if (p_Type == nullptr)
		return "";

	if (p_Type->m_Type == VariableTypes::Class)
	{
		auto s_Type = (ClassVariableType*) p_Type;
		return s_Type->m_ClassType->m_Name;
	}

	if (p_Type->m_Type == VariableTypes::ClassPointer)
	{
		auto s_Type = (ClassVariablePointerType*) p_Type;
		return s_Type->m_ClassType->m_Name;
	}

	if (p_Type->m_Type == VariableTypes::Array)
	{
		auto s_Type = (ArrayVariableType*) p_Type;
		return GetTypeFromVariableType(s_Type->m_InnerType);
	}

	return "";
}