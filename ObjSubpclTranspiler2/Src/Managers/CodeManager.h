#pragma once

#include <Misc/StdAfx.h>
#include <Utils/CodeWriter.h>

namespace Managers
{
	class CodeManager
	{
	public:
		static Utils::CodeWriter* Writer();

	private:
		static Utils::CodeWriter* m_Writer;
	};
}