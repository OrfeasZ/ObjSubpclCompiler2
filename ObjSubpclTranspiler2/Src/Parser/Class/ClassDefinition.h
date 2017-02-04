#pragma once

#include <Misc/StdAfx.h>

#include <Parser/Procedure/Procedure.h>

#include <tuple>

namespace Parser
{
	class Procedure;
	class ClassHeader;
	class VariableType;
	class VariableSeq;

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
		bool HasMember(const std::string& p_Name, VariableType*& p_Type);
		bool HasMethod(const std::string& p_Name, std::string& p_MethodName, bool p_CheckParent = false);
		bool HasVirtualMethod(const std::string& p_Name);

	private:
		std::vector<std::tuple<std::string, Procedure*>> GetAllVirtualMethods();
		std::vector<std::tuple<std::string, Procedure*>> GetFinalVirtualMethods();
		std::vector<Procedure*> GetUniqueVirtualMethods();

	private:
		void GenerateStruct(ClassDefinition* p_Parent);
		void GenerateForwardDeclarations(ClassDefinition* p_Parent);

		void GenerateVtable(ClassDefinition* p_Parent);
		void GenerateVtableTypedefs(ClassDefinition* p_Parent);
		void GenerateVtableStructure(ClassDefinition* p_Parent);
		void GenerateVtableVariable(ClassDefinition* p_Parent);

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