#include "ClassBody.h"

#include "Procedure.h"

using namespace Parser;

ClassBody::ClassBody(Procedure* p_Constructor, ProcedureSeq* p_Procedures) :
	m_Constructor(p_Constructor),
	m_Procedures(p_Procedures)
{

}

void ClassBody::Generate()
{

}