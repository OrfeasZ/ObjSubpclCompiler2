#pragma once

#include <Misc/StdAfx.h>

#include <unordered_map>

namespace Parser
{
	class ClassDefinition;
}

namespace Managers
{
	class ClassManager
	{
	public:
		static void RegisterClass(Parser::ClassDefinition* p_Class);
		static Parser::ClassDefinition* GetClass(const std::string& p_Name);

	private:
		static std::unordered_map<std::string, Parser::ClassDefinition*> m_Classes;
	};
}