#include "Real.h"

using namespace Parser;

Real::Real(const std::string& p_Left, const std::string& p_Right)
{
	std::stringstream s_Stream(p_Left + "." + p_Right);
	s_Stream >> m_Value;
}