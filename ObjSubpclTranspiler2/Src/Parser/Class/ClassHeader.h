#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class Identifier;

	class ClassHeader
	{
	public:
		ClassHeader(Identifier* p_Name, Identifier* p_Extends = nullptr);
		
	public:
		Identifier* m_Name;
		Identifier* m_Extends;
	};
}