#pragma once

#include <Misc/StdAfx.h>

#include "GeneratableChild.h"

namespace Parser
{
	class Identifier;
	typedef std::vector<Identifier*> IDSeq;
	
	class VariableType;
	class ClassVariableType;

	class VariableDeclaration :
		public GeneratableChild
	{
	public:
		VariableDeclaration(IDSeq* p_IDs, VariableType* p_Type);
	
	public:
		virtual void Generate() override;
		void GenerateClassPointer(const std::string& p_Name);
		void GenerateClass(const std::string& p_Name, ClassVariableType* p_Type = nullptr);
		void GenerateArray(const std::string& p_Name);

		void Initialize();
		void InitializeClass(const std::string& p_Name, ClassVariableType* p_Type = nullptr);
		void InitializeArray(const std::string& p_Name);

	public:
		IDSeq* m_IDs;
		VariableType* m_Type;
	};

	class VariableSeq :
		public std::vector<VariableDeclaration*>,
		public GeneratableChild
	{
	public:
		virtual void Generate() override
		{
			for (auto s_Variable : *this)
			{
				s_Variable->SetParents(this);
				s_Variable->Generate();
			}
		}

		void Initialize()
		{
			for (auto s_Variable : *this)
			{
				s_Variable->SetParents(this);
				s_Variable->Initialize();
			}
		}

		bool HasVariable(const std::string& p_Name, VariableType*& p_Type);
	};
}