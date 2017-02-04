#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class GeneratableChild;

	class Identifier
	{
	public:
		Identifier(const std::string& p_Name);

		std::string GenerateMemberAccessor(GeneratableChild* p_ChildData, const std::string& p_ClassName);
		std::string GenerateCallAccessor(GeneratableChild* p_ChildData, const std::string& p_ClassName, bool& p_Class);

	public:
		std::string m_Name;
	};

	typedef std::vector<Identifier*> IDSeq;
}