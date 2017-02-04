#pragma once

#include "BaseExpression.h"

namespace Parser
{
	class Identifier;
	class VariableType;

	class IDExpression :
		public BaseExpression
	{
	public:
		IDExpression(Identifier* p_ID);

	public:
		virtual void Generate() override;
		virtual std::string ToString() override;
		virtual bool IsID() override { return true; }
		virtual std::string GetType() override;

	private:
		std::string GetTypeFromVariableType(VariableType* p_Type);

	public:
		Identifier* m_ID;
	};
}