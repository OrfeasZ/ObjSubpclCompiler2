#pragma once

#include <Misc/StdAfx.h>

#include "Expressions/ArrayExpression.h"
#include "Expressions/BinaryExpression.h"
#include "Expressions/Call.h"
#include "Expressions/IDExpression.h"
#include "Expressions/IExpression.h"
#include "Expressions/Integer.h"
#include "Expressions/MemberCall.h"
#include "Expressions/MemberValue.h"
#include "Expressions/Real.h"
#include "Expressions/UnaryExpression.h"

#include "Statements/AssignmentStatement.h"
#include "Statements/IfStatement.h"
#include "Statements/IStatement.h"
#include "Statements/ReturnStatement.h"
#include "Statements/WhileStatement.h"

#include "Class/ClassBody.h"
#include "Class/ClassDefinition.h"
#include "Class/ClassHeader.h"
#include "Class/ClassVariableType.h"

#include "Procedure/Procedure.h"
#include "Procedure/ProcedureBody.h"
#include "Procedure/ProcedureHeader.h"

#include "ArrayVariableType.h"
#include "Body.h"
#include "Identifier.h"
#include "IParserType.h"
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