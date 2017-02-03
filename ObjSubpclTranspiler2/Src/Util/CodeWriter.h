/*
 * ObjSubpclTranspiler
 * Copyright (c) 2016, Orfeas Zafeiris
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

#include <sstream>

namespace Util
{
	class CodeWriter
	{
	public:
		CodeWriter();

	public:
		void Write(const std::string& p_Value = "");
		void Write(int64_t p_Value);
		void Write(double p_Value);

		void WriteInd(const std::string& p_Value = "");
		void WriteInd(int64_t p_Value);
		void WriteInd(double p_Value);

		void WriteLn(const std::string& p_Value = "");
		void WriteLn(int64_t p_Value);
		void WriteLn(double p_Value);

		void WriteLnInd(const std::string& p_Value = "");
		void WriteLnInd(int64_t p_Value);
		void WriteLnInd(double p_Value);

		void AddIndent();
		void RemoveIndent();
		void WriteIndent();

	public:
		inline std::string GetBuffer()
		{
			return m_Stream.str();
		}

	protected:
		std::ostringstream m_Stream;
		uint64_t m_IndentLevel;
	};
}