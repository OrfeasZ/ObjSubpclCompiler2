#pragma once

#include "Identifier.h"
#include "Body.h"

namespace Parser
{
	class Identifier;
	class Body;

	class Program
	{
	public:
		Program(Identifier* p_ID, Body* p_Body);

	public:
		void Generate();

	private:
		void GenerateClassDefinitions();
		void GenerateStaticVariables();
		void GenerateMethods();
		void GenerateClassBodies();
		void GenerateMain();

	public:
		Identifier* m_ID;
		Body* m_Body;
	};
}