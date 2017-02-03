#include "Integer.h"

using namespace Parser;

Integer::Integer(const std::string& p_Value)
{
	std::stringstream s_Stream(p_Value);
	s_Stream >> m_Value;
}

void Integer::Generate()
{

}