#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class GeneratableChild;

	class Identifier
	{
	public:
		Identifier(const std::string& p_Name);

		std::string GenerateMemberAccessor(GeneratableChild* p_ChildData);
		std::string GenerateCallAccessor(GeneratableChild* p_ChildData, bool& p_Class);

	public:
		std::string m_Name;
	};

	typedef std::vector<Identifier*> IDSeq;
}