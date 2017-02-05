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

#include "WhileStatement.h"

#include <Parser/Expressions/BaseExpression.h>

using namespace Parser;

WhileStatement::WhileStatement(BaseExpression* p_WhileExpression, IStatement* p_DoStatement) :
	m_WhileExpression(p_WhileExpression),
	m_DoStatement(p_DoStatement)
{

}

void WhileStatement::Generate()
{
	m_WhileExpression->SetParents(this);
	m_DoStatement->SetParents(this);
	
	Managers::CodeManager::Writer()->Write("while (");
	m_WhileExpression->Generate();
	Managers::CodeManager::Writer()->WriteLn(")");
	Managers::CodeManager::Writer()->WriteLnInd("{");
	Managers::CodeManager::Writer()->AddIndent();

	m_DoStatement->Generate();

	Managers::CodeManager::Writer()->RemoveIndent();
	Managers::CodeManager::Writer()->WriteInd("}");
}