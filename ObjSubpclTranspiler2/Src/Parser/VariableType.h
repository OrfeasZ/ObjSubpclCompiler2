#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	namespace VariableTypes
	{
		enum type
		{
			Integer,
			Real,
			Array,
			Class,
			ClassPointer
		};
	}

	class VariableType
	{
	public:
		VariableType(VariableTypes::type p_Type);
	
	public:
		virtual std::string ToString();

	public:
		VariableTypes::type m_Type;
	};
}