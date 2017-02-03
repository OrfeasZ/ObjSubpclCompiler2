#include "Program.h"

#include "Identifier.h"
#include "Body.h"

#include <Managers/CodeManager.h>

#include <Parser/Class/ClassDefinition.h>

#include <Parser/Expressions/Integer.h>
#include <Parser/VariableDeclaration.h>
#include <Parser/ArrayVariableType.h>
#include <Parser/VariableType.h>

using namespace Parser;

Program::Program(Identifier* p_ID, Body* p_Body) :
	m_ID(p_ID),
	m_Body(p_Body)
{
}

void Program::Generate()
{
	GenerateStaticVariables();
	GenerateMethods();
	GenerateClasses();
	GenerateMain();
}

void Program::GenerateStaticVariables()
{
	if (!m_Body->m_Variables)
		return;

	for (auto s_Variable : *m_Body->m_Variables)
	{
		for (auto s_ID : *s_Variable->m_IDs)
		{
			Managers::CodeManager::Writer()->WriteInd("static " + s_Variable->m_Type->ToString() + " " + s_ID->m_Name);

			// If this is an array then add the element count after the variable name.
			if (s_Variable->m_Type->m_Type == VariableTypes::Array)
			{
				auto s_Type = (ArrayVariableType*)s_Variable->m_Type;
				Managers::CodeManager::Writer()->Write("[");
				Managers::CodeManager::Writer()->Write(s_Type->m_ElementCount->m_Value);
				Managers::CodeManager::Writer()->Write("]");
			}

			Managers::CodeManager::Writer()->WriteLn(";");
		}
	}
}

void Program::GenerateMethods()
{
	if (!m_Body->m_Procedures)
		return;
}

void Program::GenerateClasses()
{
	if (!m_Body->m_Classes)
		return;

	for (auto s_Class : *m_Body->m_Classes)
		s_Class->Generate();
}

void Program::GenerateMain()
{
	Managers::CodeManager::Writer()->WriteLnInd("void main()");
	Managers::CodeManager::Writer()->WriteLnInd("{");

	// TODO: Write main body statements.

	Managers::CodeManager::Writer()->WriteLnInd("}");
}
