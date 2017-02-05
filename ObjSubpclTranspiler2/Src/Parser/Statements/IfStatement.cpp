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

#include "IfStatement.h"

#include <Parser/Expressions/BaseExpression.h>

using namespace Parser;

IfStatement::IfStatement(BaseExpression* p_IfExpression, IStatement* p_ThenStatement, IStatement* p_ElseStatement) :
	m_IfExpression(p_IfExpression),
	m_ThenStatement(p_ThenStatement),
	m_ElseStatement(p_ElseStatement)
{

}

void IfStatement::Generate()
{
	m_IfExpression->SetParents(this);
	m_ThenStatement->SetParents(this);

	if (m_ElseStatement)
		m_ElseStatement->SetParents(this);

	Managers::CodeManager::Writer()->Write("if (");
	m_IfExpression->Generate();
	Managers::CodeManager::Writer()->WriteLn(")");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	Managers::CodeManager::Writer()->WriteIndent();
	m_ThenStatement->Generate();
	Managers::CodeManager::Writer()->WriteLn(";");

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteInd("}");

	if (m_ElseStatement == nullptr)
		return;
	
	Managers::CodeManager::Writer()->WriteLn();
	Managers::CodeManager::Writer()->WriteLnInd("else");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	Managers::CodeManager::Writer()->WriteIndent();
	m_ElseStatement->Generate();
	Managers::CodeManager::Writer()->WriteLn(";");

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteInd("}");
}