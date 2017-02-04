#pragma once

#include <Misc/StdAfx.h>

#include <Parser/Procedure/Procedure.h>

namespace Parser
{
	class Procedure;
	class ClassHeader;
	class VariableType;

	class VariableDeclaration;
	typedef std::vector<VariableDeclaration*> VariableSeq;

	class ClassBody;

	class ClassDefinition
	{
	public:
		ClassDefinition(ClassHeader* p_Header, VariableSeq* p_Variables, ClassBody* p_Body);
		
	public:
		void GenerateDefinitions();
		void GenerateBody();

		std::vector<Procedure*> GetMethods(ProcedureType::type p_Type = ProcedureType::Standard);

		bool IsAbstract();
		bool HasMember(const std::string& p_Name);
		bool HasMethod(const std::string& p_Name, bool& p_Virtual, bool p_CheckParent = false);

	private:
		void GenerateStruct(ClassDefinition* p_Parent);
		void GenerateVtable(ClassDefinition* p_Parent);
		void GenerateConstructor(ClassDefinition* p_Parent);
		void GenerateMethods(ClassDefinition* p_Parent);
		void GenerateMethod(Procedure* p_Procedure);

	public:
		ClassHeader* m_Header;
		VariableSeq* m_Variables;
		ClassBody* m_Body;
	};

	typedef std::vector<ClassDefinition*> ClassSeq;
}