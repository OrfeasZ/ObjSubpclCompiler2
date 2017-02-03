#pragma once

#include "VariableType.h"

namespace Parser
{
	class Integer;

	class ArrayVariableType :
		public VariableType
	{
	public:
		ArrayVariableType(VariableType* p_InnerType, Integer* p_ElementCount);

	public:
		virtual void Generate() override;

	public:
		VariableType* m_InnerType;
		Integer* m_ElementCount;
	};
}