#pragma once

#include <Misc/StdAfx.h>
#include <Util/CodeWriter.h>

namespace Managers
{
	class CodeManager
	{
	public:
		static Util::CodeWriter* Writer();

	private:
		static Util::CodeWriter* m_Writer;
	};
}