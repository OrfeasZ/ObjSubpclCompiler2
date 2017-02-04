#include "Program.h"

#include "Identifier.h"
#include "Body.h"

#include <Managers/CodeManager.h>

#include <Parser/Class/ClassDefinition.h>

#include <Parser/Expressions/Integer.h>
#include <Parser/VariableDeclaration.h>
#include <Parser/ArrayVariableType.h>
#include <Parser/VariableType.h>
#include <Parser/Procedure/Procedure.h>
#include <Parser/Procedure/ProcedureHeader.h>
#include <Parser/Procedure/ProcedureBody.h>
#include <Parser/Statements/IStatement.h>

#include <Util/Utils.h>

using namespace Parser;

Program::Program(Identifier* p_ID, Body* p_Body) :
	m_ID(p_ID),
	m_Body(p_Body)
{
}

void Program::Generate()
{
	GenerateHeader();
	GenerateClassDefinitions();
	GenerateStaticVariables();
	GenerateMethods();
	GenerateClassBodies();
	GenerateMain();
}

void Program::GenerateHeader()
{
	// Write the disclaimer.
	Managers::CodeManager::Writer()->WriteLnInd("// Code generated by ObjSubpclTranspiler2 - DO NOT EDIT");
	Managers::CodeManager::Writer()->WriteLnInd("// Remember to compile with -fms-extensions");
	Managers::CodeManager::Writer()->WriteLn();

	// Write our includes.
	Managers::CodeManager::Writer()->WriteLnInd("#include <stdio.h>");
	Managers::CodeManager::Writer()->WriteLnInd("#include <string.h>");
	Managers::CodeManager::Writer()->WriteLn();
}

void Program::GenerateClassDefinitions()
{
	if (!m_Body->m_Classes)
		return;

	Managers::CodeManager::Writer()->WriteLnInd("// Class definitions");

	for (auto s_Class : *m_Body->m_Classes)
		s_Class->GenerateDefinitions();
}

void Program::GenerateStaticVariables()
{
	if (!m_Body->m_Variables)
		return;

	Managers::CodeManager::Writer()->WriteLnInd("// Global program variables");
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

	Managers::CodeManager::Writer()->WriteLn();
}

void Program::GenerateMethods()
{
	if (!m_Body->m_Procedures)
		return;

	Managers::CodeManager::Writer()->WriteLnInd("// Global program methods");
	for (auto s_Procedure : *m_Body->m_Procedures)
	{
		auto s_Parameters = s_Procedure->m_Header->GetParameters();
		auto s_FinalParameters = Util::Utils::Join(s_Parameters, ", ");

		Managers::CodeManager::Writer()->WriteLnInd("void " + s_Procedure->m_Header->m_Name->m_Name + "(" + s_FinalParameters + ")");
		Managers::CodeManager::Writer()->WriteLnInd("{");
		Managers::CodeManager::Writer()->AddIndent();

		// TODO: Generate method scoped variables.
		
		// Generate method statements.
		s_Procedure->m_Body->m_Body->SetParents(s_Procedure->m_Header->m_Parameters, s_Procedure->m_Body->m_Variables, nullptr);
		s_Procedure->m_Body->m_Body->Generate();

		Managers::CodeManager::Writer()->RemoveIndent();
		Managers::CodeManager::Writer()->WriteLnInd("}");
		Managers::CodeManager::Writer()->WriteLn();
	}
}

void Program::GenerateClassBodies()
{
	if (!m_Body->m_Classes)
		return;

	Managers::CodeManager::Writer()->WriteLnInd("// Class methods");

	for (auto s_Class : *m_Body->m_Classes)
		s_Class->GenerateBody();
}

void Program::GenerateMain()
{
	Managers::CodeManager::Writer()->WriteLnInd("// Program entry point");
	Managers::CodeManager::Writer()->WriteLnInd("void main()");
	Managers::CodeManager::Writer()->WriteLnInd("{");

	// TODO: Initialize global variables.
	// TODO: Generate main scoped variables.
	// TODO: Generate main statements.

	Managers::CodeManager::Writer()->WriteLnInd("}");
	Managers::CodeManager::Writer()->WriteLn();
}
