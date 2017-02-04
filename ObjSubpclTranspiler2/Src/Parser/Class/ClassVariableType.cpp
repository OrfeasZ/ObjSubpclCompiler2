#include "ClassVariableType.h"

#include <Parser/Identifier.h>
#include <Parser/Expressions/BaseExpression.h>

#include <Managers/ClassManager.h>

using namespace Parser;

ClassVariableType::ClassVariableType(Identifier* p_ClassType, ExpressionSeq* p_Arguments) :
	VariableType(VariableTypes::Class),
	m_ClassType(p_ClassType),
	m_Arguments(p_Arguments)
{
}

std::string ClassVariableType::ToString()
{
	// Check to see if the class we're referencing exists.
	if (Managers::ClassManager::GetClass(m_ClassType->m_Name) == nullptr)
		throw std::exception(("Could not find class '" + m_ClassType->m_Name + "' used for a variable.").c_str());

	return "struct " + m_ClassType->m_Name + "_t";
}