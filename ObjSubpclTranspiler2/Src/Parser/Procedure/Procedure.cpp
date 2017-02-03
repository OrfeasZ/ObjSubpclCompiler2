#include "Procedure.h"

#include "ProcedureHeader.h"
#include "ProcedureBody.h"

using namespace Parser;

Procedure::Procedure(ProcedureHeader* p_Header, ProcedureBody* p_Body) :
	m_Header(p_Header),
	m_Body(p_Body),
	m_Type(ProcedureType::Standard)
{

}

void Procedure::Generate()
{

}