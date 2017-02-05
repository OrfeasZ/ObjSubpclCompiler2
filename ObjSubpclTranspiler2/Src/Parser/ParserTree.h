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

#include "Expressions/ArrayExpression.h"
#include "Expressions/BinaryExpression.h"
#include "Expressions/Call.h"
#include "Expressions/IDExpression.h"
#include "Expressions/BaseExpression.h"
#include "Expressions/Integer.h"
#include "Expressions/MemberCall.h"
#include "Expressions/MemberValue.h"
#include "Expressions/Real.h"
#include "Expressions/UnaryExpression.h"

#include "Statements/AssignmentStatement.h"
#include "Statements/IfStatement.h"
#include "Statements/IStatement.h"
#include "Statements/NewStatement.h"
#include "Statements/ReturnStatement.h"
#include "Statements/WhileStatement.h"

#include "Class/ClassBody.h"
#include "Class/ClassDefinition.h"
#include "Class/ClassHeader.h"
#include "Class/ClassVariablePointerType.h"
#include "Class/ClassVariableType.h"

#include "Procedure/Procedure.h"
#include "Procedure/ProcedureBody.h"
#include "Procedure/ProcedureHeader.h"

#include "ArrayVariableType.h"
#include "Body.h"
#include "Identifier.h"
#include "Program.h"
#include "VariableDeclaration.h"
#include "VariableType.h"

extern void yyerror(const char* p_Error);

namespace Parser
{
	class ParserTree
	{
	public:
		static void SetProgram(Program* p_Program)
		{
			m_Program = p_Program;
		}

		static Program* GetProgram()
		{
			return m_Program;
		}

	protected:
		static Program* m_Program;
	};
}