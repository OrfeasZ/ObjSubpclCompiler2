#include "NewStatement.h"

#include <Parser/Expressions/BaseExpression.h>

#include <Managers/ClassManager.h>
#include <Managers/CodeManager.h>

#include <Util/Utils.h>

#include <Parser/Class/ClassDefinition.h>
#include <Parser/Class/ClassHeader.h>>

#include <Parser/Identifier.h>

using namespace Parser;

NewStatement::NewStatement(BaseExpression* p_LeftExpression, Identifier* p_ClassName, ExpressionSeq* p_Arguments) :
	m_LeftExpression(p_LeftExpression),
	m_ClassName(p_ClassName),
	m_Arguments(p_Arguments)
{

}

void NewStatement::Generate()
{
	m_LeftExpression->SetParents(this);

	auto s_Class = Managers::ClassManager::GetClass(m_ClassName->m_Name);

	if (s_Class == nullptr)
		throw new std::exception(("Could not find class '" + m_ClassName->m_Name + "' used in a new statement.").c_str());

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

	// Generate our member expression.
	auto s_Expression = m_LeftExpression->ToString();

	// Add it as the first argument.
	s_Arguments.insert(s_Arguments.begin(), s_Expression);

	std::string s_ClassName = s_Class->m_Header->m_Name->m_Name;
	std::string s_ClassType = s_ClassName + "_t";
	std::string s_ClassCtor = s_ClassName + "__ctor";

	// TODO: Get type of container from expression.
	std::string s_VariableType = s_ClassType;

	// Allocate the member.
	Managers::CodeManager::Writer()->WriteLn(s_Expression + " = (" + s_VariableType + "*) malloc(sizeof(" + s_ClassType + "));");

	// Call the constructor.
	Managers::CodeManager::Writer()->WriteInd(s_ClassCtor + "(" + Util::Utils::Join(s_Arguments, ", ") + ")");
}