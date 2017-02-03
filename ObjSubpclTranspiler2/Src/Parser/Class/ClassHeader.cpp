#include "ClassHeader.h"

#include <Parser/Identifier.h>

using namespace Parser;

ClassHeader::ClassHeader(Identifier* p_Name, Identifier* p_Extends) :
	m_Name(p_Name),
	m_Extends(p_Extends)
{

}

void ClassHeader::Generate()
{

}