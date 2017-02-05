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

#include "NewStatement.h"

#include <Parser/Expressions/BaseExpression.h>

#include <Managers/ClassManager.h>
#include <Managers/CodeManager.h>

#include <Util/Utils.h>

#include <Parser/Class/ClassDefinition.h>
#include <Parser/Class/ClassHeader.h>

#include <Parser/Identifier.h>

using namespace Parser;

NewStatement::NewStatement(BaseExpression* p_LeftExpression, Identifier* p_ClassName, ExpressionSeq* p_Arguments) :
	m_LeftExpression(p_LeftExpression),
	m_ClassName(p_ClassName),
	m_Arguments(p_Arguments)
{

}

void NewStatement::Generate()
{
	m_LeftExpression->SetParents(this);

	auto s_Class = Managers::ClassManager::GetClass(m_ClassName->m_Name);

	if (s_Class == nullptr)
		throw std::runtime_error("Could not find class '" + m_ClassName->m_Name + "' used in a new statement.");

	if (s_Class->IsAbstract())
		throw std::runtime_error("Cannot instantiate abstract class '" + m_ClassName->m_Name + "'.");

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

	std::string s_ClassName = s_Class->m_Header->m_Name->m_Name;
	std::string s_ClassType = s_ClassName + "_t";
	std::string s_ClassCtor = s_ClassName + "__ctor";

	// Generate our member expression.
	auto s_Expression = m_LeftExpression->ToString();

	// Add it as the first argument.
	s_Arguments.insert(s_Arguments.begin(), "(struct " + s_ClassType + "*) " + s_Expression);

	// Allocate the member.
	Managers::CodeManager::Writer()->WriteLn(s_Expression + " = malloc(sizeof(struct " + s_ClassType + "));");

	// Call the constructor.
	Managers::CodeManager::Writer()->WriteInd(s_ClassCtor + "(" + Util::Utils::Join(s_Arguments, ", ") + ")");
}