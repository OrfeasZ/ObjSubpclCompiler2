#pragma once

#include <Parser/VariableType.h>

namespace Parser
{
	class Identifier;
	
	class ClassVariablePointerType :
		public VariableType
	{
	public:
		ClassVariablePointerType(Identifier* p_ClassType);

	public:
		virtual std::string ToString() override;

	public:
		Identifier* m_ClassType;
	};
}