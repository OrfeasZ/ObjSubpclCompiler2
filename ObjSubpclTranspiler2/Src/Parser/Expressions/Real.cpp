#include "Real.h"

#include <Managers/CodeManager.h>

using namespace Parser;

Real::Real(const std::string& p_Left, const std::string& p_Right)
{
	std::stringstream s_Stream(p_Left + "." + p_Right);
	s_Stream >> m_Value;
}

void Real::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string Real::ToString()
{
	std::string s_String = std::to_string(m_Value);

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}