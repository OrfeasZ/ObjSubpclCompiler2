#include "VariableDeclaration.h"

#include "Identifier.h"
#include "VariableType.h"

using namespace Parser;

VariableDeclaration::VariableDeclaration(IDSeq* p_IDs, VariableType* p_Type) :
	m_IDs(p_IDs),
	m_Type(p_Type)
{

}