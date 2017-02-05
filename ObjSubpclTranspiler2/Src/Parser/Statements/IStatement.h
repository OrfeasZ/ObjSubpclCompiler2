/*
 * ObjSubpclTranspiler
 * Copyright (c) 2016 - 2017, Orfeas Zafeiris
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright holders reserve the right to release and distribute this 
 * program under different license terms.
 */

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