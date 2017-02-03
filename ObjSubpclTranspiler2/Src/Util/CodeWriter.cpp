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

#include "CodeWriter.h"

using namespace Util;

CodeWriter::CodeWriter() :
	m_IndentLevel(0)
{
}

void CodeWriter::Write(const std::string& p_Value)
{
	m_Stream << p_Value;
}

void CodeWriter::Write(int64_t p_Value)
{
	m_Stream << p_Value;
}

void CodeWriter::Write(double p_Value)
{
	m_Stream << p_Value;
}

void CodeWriter::WriteInd(const std::string& p_Value)
{
	WriteIndent();
	m_Stream << p_Value;
}

void CodeWriter::WriteInd(int64_t p_Value)
{
	WriteIndent();
	m_Stream << p_Value;
}

void CodeWriter::WriteInd(double p_Value)
{
	WriteIndent();
	m_Stream << p_Value;
}

void CodeWriter::WriteLn(const std::string& p_Value)
{
	m_Stream << p_Value << std::endl;
}

void CodeWriter::WriteLn(int64_t p_Value)
{
	m_Stream << p_Value << std::endl;
}

void CodeWriter::WriteLn(double p_Value)
{
	m_Stream << p_Value << std::endl;
}

void CodeWriter::WriteLnInd(const std::string& p_Value)
{
	WriteIndent();
	m_Stream << p_Value << std::endl;
}

void CodeWriter::WriteLnInd(int64_t p_Value)
{
	WriteIndent();
	m_Stream << p_Value << std::endl;
}

void CodeWriter::WriteLnInd(double p_Value)
{
	WriteIndent();
	m_Stream << p_Value << std::endl;
}

void CodeWriter::AddIndent()
{
	++m_IndentLevel;
}

void CodeWriter::RemoveIndent()
{
	if (m_IndentLevel == 0)
		return;

	--m_IndentLevel;
}

void CodeWriter::WriteIndent()
{
	for (uint64_t i = 0; i < m_IndentLevel; ++i)
		m_Stream << "\t";
}
