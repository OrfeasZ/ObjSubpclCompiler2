#pragma once

#include <Misc/StdAfx.h>

#include <vector>

#include <Parser/GeneratableChild.h>

#include <Managers/CodeManager.h>

namespace Parser
{
	class IStatement : 
		virtual public GeneratableChild
	{
	public:
		virtual bool IsMemberCall() { return false; }
	};

	class StatementSeq :
		public IStatement,
		public std::vector<IStatement*>
	{
	public:
		virtual void Generate() override 
		{
			for (auto s_Statement : *this)
			{
				if (!s_Statement)
					continue;

				s_Statement->SetParents(this);
			
				Managers::CodeManager::Writer()->WriteIndent();
				s_Statement->Generate();
				Managers::CodeManager::Writer()->WriteLn(";");
			}
		}
	};
}