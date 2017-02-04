#include "Integer.h"

#include <Managers/CodeManager.h>

using namespace Parser;

Integer::Integer(const std::string& p_Value)
{
	std::stringstream s_Stream(p_Value);
	s_Stream >> m_Value;
}

void Integer::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string Integer::ToString()
{
	std::string s_String = std::to_string(m_Value);

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}