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
		void GenerateHeader();
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