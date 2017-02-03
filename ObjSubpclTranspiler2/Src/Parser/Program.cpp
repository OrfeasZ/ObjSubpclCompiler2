#include "Program.h"

#include "Identifier.h"
#include "Body.h"

using namespace Parser;

Program::Program(Identifier* p_ID, Body* p_Body) :
	m_ID(p_ID),
	m_Body(p_Body)
{
}

void Program::Generate()
{

}