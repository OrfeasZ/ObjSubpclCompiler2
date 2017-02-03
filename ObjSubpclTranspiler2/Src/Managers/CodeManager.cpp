#include "CodeManager.h"

using namespace Managers;

Utils::CodeWriter* CodeManager::m_Writer = nullptr;

Utils::CodeWriter* CodeManager::Writer()
{
	if (!m_Writer)
		m_Writer = new Utils::CodeWriter();

	return m_Writer;
}