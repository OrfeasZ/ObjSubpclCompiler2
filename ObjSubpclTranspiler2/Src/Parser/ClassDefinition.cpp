#include "ClassDefinition.h"

#include "ClassHeader.h"
#include "VariableDeclaration.h"
#include "ClassBody.h"

using namespace Parser;

ClassDefinition::ClassDefinition(ClassHeader* p_Header, VariableSeq* p_Variables, ClassBody* p_Body) :
	m_Header(p_Header),
	m_Variables(p_Variables),
	m_Body(p_Body)
{

}

void ClassDefinition::Generate()
{

}