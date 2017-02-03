#include "CodeManager.h"

using namespace Managers;

Util::CodeWriter* CodeManager::m_Writer = nullptr;

Util::CodeWriter* CodeManager::Writer()
{
	if (!m_Writer)
		m_Writer = new Util::CodeWriter();

	return m_Writer;
}