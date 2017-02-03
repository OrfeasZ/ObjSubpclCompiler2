#include "ProcedureHeader.h"

#include "Identifier.h"
#include "VariableDeclaration.h"

using namespace Parser;

ProcedureHeader::ProcedureHeader(Identifier* p_Name, VariableSeq* p_Parameters) :
	m_Name(p_Name),
	m_Parameters(p_Parameters)
{

}

void ProcedureHeader::Generate()
{

}