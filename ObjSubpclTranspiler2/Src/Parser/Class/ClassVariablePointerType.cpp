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

#include "ClassVariablePointerType.h"

#include <Parser/Identifier.h>

#include <Managers/ClassManager.h>

using namespace Parser;

ClassVariablePointerType::ClassVariablePointerType(Identifier* p_ClassType) :
	VariableType(VariableTypes::ClassPointer),
	m_ClassType(p_ClassType)
{
}

std::string ClassVariablePointerType::ToString()
{
	// Check to see if the class we're referencing exists.
	if (Managers::ClassManager::GetClass(m_ClassType->m_Name) == nullptr)
		throw std::runtime_error("Could not find class '" + m_ClassType->m_Name + "' used for a variable.");

	return "struct " + m_ClassType->m_Name + "_t";
}