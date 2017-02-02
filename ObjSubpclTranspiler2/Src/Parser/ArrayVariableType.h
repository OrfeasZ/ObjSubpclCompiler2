#pragma once

#include "VariableType.h"

namespace Parser
{
	class ArrayVariableType :
		public VariableType
	{
	public:
		ArrayVariableType(VariableType* p_InnerType, Integer* p_ElementCount) :
			VariableType(VariableTypes::Array),
			m_InnerType(p_InnerType),
			m_ElementCount(p_ElementCount)
		{

		}

	public:
		virtual void Generate()
		{

		}

	public:
		VariableType* m_InnerType;
		Integer* m_ElementCount;
	};
}