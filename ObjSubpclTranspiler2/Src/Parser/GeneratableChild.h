#pragma once

#include <Misc/StdAfx.h>

namespace Parser
{
	class VariableSeq;
	class ClassDefinition;

	class GeneratableChild
	{
	public:
		GeneratableChild() :
			m_ParentParameters(nullptr),
			m_ParentVariables(nullptr),
			m_ParentClass(nullptr)
		{
		}

	public:
		virtual void Generate() = 0;

		inline void SetParents(VariableSeq* p_ParentParameters, VariableSeq* p_ParentVariables, ClassDefinition* p_ParentClass)
		{
			m_ParentParameters = p_ParentParameters;
			m_ParentVariables = p_ParentVariables;
			m_ParentClass = p_ParentClass;
		}

		inline void SetParents(GeneratableChild* p_Other)
		{
			m_ParentParameters = p_Other->m_ParentParameters;
			m_ParentVariables = p_Other->m_ParentVariables;
			m_ParentClass = p_Other->m_ParentClass;
		}

	public:
		VariableSeq* m_ParentParameters;
		VariableSeq* m_ParentVariables;
		ClassDefinition* m_ParentClass;

	};
}