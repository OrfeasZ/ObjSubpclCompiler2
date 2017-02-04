#include "IDExpression.h"

#include <Parser/Identifier.h>

#include <Managers/CodeManager.h>

using namespace Parser;

IDExpression::IDExpression(Identifier* p_ID) :
	m_ID(p_ID)
{

}

void IDExpression::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string IDExpression::ToString()
{
	std::string s_String = m_ID->GenerateAccessor(this, false);

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}