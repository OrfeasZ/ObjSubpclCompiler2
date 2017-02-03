#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class Identifier
	{
	public:
		Identifier(const std::string& p_Name);

	public:
		std::string m_Name;
	};

	typedef std::vector<Identifier*> IDSeq;
}