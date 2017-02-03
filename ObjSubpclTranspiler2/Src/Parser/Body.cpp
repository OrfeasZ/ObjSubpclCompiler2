#include "Body.h"

#include "IStatement.h"
#include "VariableDeclaration.h"
#include "Procedure.h"
#include "ClassDefinition.h"

using namespace Parser;

Body::Body(StatementSeq* p_Body, VariableSeq* p_Variables, ProcedureSeq* p_Procedures, ClassSeq* p_Classes) :
	m_Body(p_Body),
	m_Variables(p_Variables),
	m_Procedures(p_Procedures),
	m_Classes(p_Classes)
{

}

void Body::Generate()
{

}