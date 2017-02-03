#pragma once

#include "IParserType.h"

namespace Parser
{
	namespace VariableTypes
	{
		enum type
		{
			Integer,
			Real,
			Array,
			Class
		};
	}

	class VariableType :
		public IParserType
	{
	public:
		VariableType(VariableTypes::type p_Type = VariableTypes::Integer);
	
	public:
		virtual void Generate() override;

	public:
		VariableTypes::type m_Type;
	};
}