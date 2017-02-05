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

#include "BaseExpression.h"

namespace Parser
{
	namespace BinaryExpressions
	{
		enum type
		{
			Plus,
			Minus,
			Multiply,
			Divide,
			Div,
			Mod,
			Or,
			And,
			Equal,
			NotEqual,
			LessThan,
			LessThanEqual,
			GreaterThan,
			GreaterThanEqual
		};
	}

	class BinaryExpression :
		public BaseExpression
	{
	public:
		BinaryExpression(BaseExpression* p_Left, BaseExpression* p_Right, BinaryExpressions::type p_Type);

	public:
		virtual void Generate() override;
		virtual std::string ToString() override;
		
	public:
		BaseExpression* m_Left;
		BaseExpression* m_Right;
		BinaryExpressions::type m_Type;
	};
}