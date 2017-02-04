#include "MemberValue.h"

#include <Parser/Identifier.h>

using namespace Parser;

MemberValue::MemberValue(BaseExpression* p_VariableExpression, Identifier* p_Member) :
	m_VariableExpression(p_VariableExpression),
	m_Member(p_Member)
{
}

void MemberValue::Generate()
{

}