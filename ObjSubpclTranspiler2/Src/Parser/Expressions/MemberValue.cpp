#include "MemberValue.h"

#include <Parser/Identifier.h>

#include <Managers/CodeManager.h>
#include <Managers/ClassManager.h>

#include <Parser/ParserTree.h>

using namespace Parser;

MemberValue::MemberValue(BaseExpression* p_VariableExpression, Identifier* p_Member) :
	m_VariableExpression(p_VariableExpression),
	m_Member(p_Member)
{
}

void MemberValue::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string MemberValue::ToString()
{
	std::string s_String = "";

	// TODO

	m_VariableExpression->SetParents(this);
	
	auto s_MemberType = m_VariableExpression->GetType();
	auto s_MemberExpression = m_VariableExpression->ToString();
	auto s_ClassType = Managers::ClassManager::GetClass(s_MemberType);

	if (s_ClassType == nullptr)
		throw std::exception(("Tried access member variable '" + m_Member->m_Name + "' on a variable of unknown type.").c_str());

	auto s_TempParent = m_ParentClass;
	m_ParentClass = s_ClassType;

	bool s_Class = true;
	s_String += m_Member->GenerateMemberAccessor(this, s_MemberExpression);

	m_ParentClass = s_TempParent;

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}

std::string MemberValue::GetType()
{
	// TODO: Get member value type.
	m_VariableExpression->SetParents(this);

	auto s_MemberType = m_VariableExpression->GetType();
	auto s_ClassType = Managers::ClassManager::GetClass(s_MemberType);

	if (s_ClassType == nullptr)
		throw std::exception(("Tried access member variable '" + m_Member->m_Name + "' on a variable of unknown type.").c_str());

}