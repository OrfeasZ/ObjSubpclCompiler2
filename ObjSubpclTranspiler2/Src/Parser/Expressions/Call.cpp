#include "Call.h"

#include <Parser/Identifier.h>
#include <Parser/Expressions/BaseExpression.h>

#include <Managers/CodeManager.h>

using namespace Parser;

Call::Call(Identifier* p_Name, ExpressionSeq* p_Arguments) :
	m_Name(p_Name),
	m_Arguments(p_Arguments)
{

}

void Call::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string Call::ToString()
{
	std::string s_String = "";


	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}