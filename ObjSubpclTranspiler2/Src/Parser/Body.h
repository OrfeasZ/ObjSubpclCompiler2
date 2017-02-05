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

#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class StatementSeq;
	class VariableSeq;

	class Procedure;
	typedef std::vector<Procedure*> ProcedureSeq;

	class ClassDefinition;
	typedef std::vector<ClassDefinition*> ClassSeq;

	class Body
	{
	public:
		Body(StatementSeq* p_Body, VariableSeq* p_Variables = nullptr, ProcedureSeq* p_Procedures = nullptr, ClassSeq* p_Classes = nullptr);

	public:
		StatementSeq* m_Body;
		VariableSeq* m_Variables;
		ProcedureSeq* m_Procedures;
		ClassSeq* m_Classes;
	};
}