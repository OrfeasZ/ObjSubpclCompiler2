#include "VariableDeclaration.h"

#include "Identifier.h"
#include "VariableType.h"

using namespace Parser;

VariableDeclaration::VariableDeclaration(IDSeq* p_IDs, VariableType* p_Type) :
	m_IDs(p_IDs),
	m_Type(p_Type)
{

}

bool VariableSeq::HasVariable(const std::string& p_Name, VariableType*& p_Type)
{
	for (auto s_Variable : *this)
	{
		for (auto s_ID : *s_Variable->m_IDs)
		{
			if (s_ID->m_Name == p_Name)
			{
				p_Type = s_Variable->m_Type;
				return true;
			}
		}
	}

	return false;
}