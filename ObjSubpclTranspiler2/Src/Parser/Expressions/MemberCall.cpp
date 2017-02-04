#include "MemberCall.h"

#include <Parser/Identifier.h>

#include <Managers/CodeManager.h>
#include <Managers/ClassManager.h>

#include <Parser/Expressions/IDExpression.h>
#include <Parser/Class/ClassDefinition.h>
#include <Parser/Class/ClassHeader.h>

#include <Util/Utils.h>

using namespace Parser;

MemberCall::MemberCall(BaseExpression* p_VariableExpression, Identifier* p_Name, ExpressionSeq* p_Arguments) :
	Call(p_Name, p_Arguments),
	m_VariableExpression(p_VariableExpression)
{
}

void MemberCall::Generate()
{
	Managers::CodeManager::Writer()->Write(ToString());
}

std::string MemberCall::ToString()
{
	std::string s_String = "";

	// TODO
	
	// Is this a super call?
	bool s_SuperCall = false;
	if (m_VariableExpression->IsID())
	{
		auto s_Expression = (IDExpression*) m_VariableExpression;
		s_SuperCall = s_Expression->m_ID->m_Name == "super";
	}
	
	m_VariableExpression->SetParents(this);

	if (!s_SuperCall || m_ParentClass == nullptr)
	{
		m_VariableExpression->ToString();
		// TODO: Get type of expression.
	}
	else
	{
		// Special handling for super calls.
		if (m_ParentClass->m_Header->m_Extends == nullptr)
			throw std::exception(("Trying to call function '" + m_Name->m_Name + "' on non-existent base class.").c_str());

		if (m_Name->m_Name == "ctor")
		{
			// We skip constructor calls as those are handled by the class definition constructo generator.
			return "";
		}
		else
		{
			auto s_TempParent = m_ParentClass;
			m_ParentClass = Managers::ClassManager::GetClass(m_ParentClass->m_Header->m_Extends->m_Name);

			bool s_Class = true;
			s_String += m_Name->GenerateCallAccessor(this, s_Class);

			m_ParentClass = s_TempParent;
		}

		std::vector<std::string> s_Arguments;

		// Serialize our arguments.
		if (m_Arguments)
		{
			for (auto s_Expression : *m_Arguments)
			{
				s_Expression->SetParents(this);
				s_Arguments.push_back(s_Expression->ToString());
			}
		}

		// If this is a class call add th as the first argument.
		s_Arguments.insert(s_Arguments.begin(), "th");

		s_String += "(" + Util::Utils::Join(s_Arguments, ", ") + ")";
	}

	if (m_Enclosed)
		s_String = "(" + s_String + ")";

	return s_String;
}