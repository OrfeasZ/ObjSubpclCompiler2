#include "ProcedureBody.h"

#include <Parser/Statements/IStatement.h>
#include <Parser/VariableDeclaration.h>

using namespace Parser;

ProcedureBody::ProcedureBody(StatementSeq* p_Body, VariableSeq* p_Variables) :
	m_Body(p_Body),
	m_Variables(p_Variables)
{

}