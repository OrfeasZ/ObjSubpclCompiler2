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

#include "GeneratableChild.h"

namespace Parser
{
	class Identifier;
	typedef std::vector<Identifier*> IDSeq;
	
	class VariableType;
	class ClassVariableType;

	class VariableDeclaration :
		public GeneratableChild
	{
	public:
		VariableDeclaration(IDSeq* p_IDs, VariableType* p_Type);
	
	public:
		virtual void Generate() override;
		void GenerateClassPointer(const std::string& p_Name);
		void GenerateClass(const std::string& p_Name, ClassVariableType* p_Type = nullptr);
		void GenerateArray(const std::string& p_Name);

		void Initialize();
		void InitializeClass(const std::string& p_Name, ClassVariableType* p_Type = nullptr);
		void InitializeArray(const std::string& p_Name);

	public:
		IDSeq* m_IDs;
		VariableType* m_Type;
	};

	class VariableSeq :
		public std::vector<VariableDeclaration*>,
		public GeneratableChild
	{
	public:
		virtual void Generate() override
		{
			for (auto s_Variable : *this)
			{
				s_Variable->SetParents(this);
				s_Variable->Generate();
			}
		}

		void Initialize()
		{
			for (auto s_Variable : *this)
			{
				s_Variable->SetParents(this);
				s_Variable->Initialize();
			}
		}

		bool HasVariable(const std::string& p_Name, VariableType*& p_Type);
	};
}