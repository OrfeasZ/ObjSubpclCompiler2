#include "ClassVariablePointerType.h"

#include <Parser/Identifier.h>

#include <Managers/ClassManager.h>

using namespace Parser;

ClassVariablePointerType::ClassVariablePointerType(Identifier* p_ClassType) :
	VariableType(VariableTypes::ClassPointer),
	m_ClassType(p_ClassType)
{
}

std::string ClassVariablePointerType::ToString()
{
	// Check to see if the class we're referencing exists.
	if (Managers::ClassManager::GetClass(m_ClassType->m_Name) == nullptr)
		throw new std::exception(("Could not find class '" + m_ClassType->m_Name + "' used for a variable.").c_str());

	return "struct " + m_ClassType->m_Name + "_t";
}