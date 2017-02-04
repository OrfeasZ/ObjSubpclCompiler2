#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class VariableDeclaration;
	typedef std::vector<VariableDeclaration*> VariableSeq;

	class ClassDefinition;

	class GeneratableChild
	{
	public:
		GeneratableChild() :
			m_Parameters(nullptr),
			m_Parent(nullptr)
		{
		}

	public:
		virtual void Generate() = 0;

	public:
		VariableSeq* m_Parameters;
		ClassDefinition* m_Parent;
	};
}