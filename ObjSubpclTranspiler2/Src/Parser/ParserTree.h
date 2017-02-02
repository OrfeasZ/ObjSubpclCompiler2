#pragma once

#include <Misc/StdAfx.h>

#include "AbstractProcedure.h"
#include "ArrayExpression.h"
#include "ArrayVariableType.h"
#include "AssignmentStatement.h"
#include "BinaryExpression.h"
#include "Body.h"
#include "Call.h"
#include "ClassBody.h"
#include "ClassDefinition.h"
#include "ClassHeader.h"
#include "ClassVariableType.h"
#include "Identifier.h"
#include "IDExpression.h"
#include "IExpression.h"
#include "IfStatement.h"
#include "Integer.h"
#include "IParserType.h"
#include "IStatement.h"
#include "MemberCall.h"
#include "MemberValue.h"
#include "Procedure.h"
#include "ProcedureBody.h"
#include "ProcedureHeader.h"
#include "Program.h"
#include "Real.h"
#include "ReturnStatement.h"
#include "UnaryExpression.h"
#include "VariableDeclaration.h"
#include "VariableType.h"
#include "WhileStatement.h"

extern void yyerror(const char* p_Error);

namespace Parser
{
	class ParserTree
	{

	};
}