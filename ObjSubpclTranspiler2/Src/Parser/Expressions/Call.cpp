#include "Call.h"

#include <Parser/Identifier.h>
#include <Parser/Expressions/IExpression.h>

using namespace Parser;

Call::Call(Identifier* p_Name, ExpressionSeq* p_Arguments) :
	m_Name(p_Name),
	m_Arguments(p_Arguments)
{

}

void Call::Generate()
{

}