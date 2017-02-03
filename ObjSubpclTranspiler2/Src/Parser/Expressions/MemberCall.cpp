#include "MemberCall.h"

#include <Parser/Identifier.h>

using namespace Parser;

MemberCall::MemberCall(IExpression* p_VariableExpression, Identifier* p_Name, ExpressionSeq* p_Arguments) :
	Call(p_Name, p_Arguments),
	m_VariableExpression(p_VariableExpression)
{
}