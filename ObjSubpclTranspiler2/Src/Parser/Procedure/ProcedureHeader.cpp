#include "ProcedureHeader.h"

#include <Parser/Identifier.h>
#include <Parser/VariableDeclaration.h>
#include <Parser/Identifier.h>
#include <Parser/VariableType.h>

using namespace Parser;

ProcedureHeader::ProcedureHeader(Identifier* p_Name, VariableSeq* p_Parameters) :
	m_Name(p_Name),
	m_Parameters(p_Parameters)
{

}

std::vector<std::string> ProcedureHeader::GetParameters()
{
	std::vector<std::string> s_Parameters;

	if (!m_Parameters)
		return s_Parameters;

	for (auto s_ParameterGroup : *m_Parameters)
	{
		for (auto s_ID : *s_ParameterGroup->m_IDs)
		{
			std::string s_Parameter = s_ParameterGroup->m_Type->ToString();

			if (s_ParameterGroup->m_Type->m_Type == VariableTypes::Class)
				s_Parameter += "*";
			else if (s_ParameterGroup->m_Type->m_Type == VariableTypes::Array)
				s_Parameter += "**";

			s_Parameter += " " + s_ID->m_Name;
			s_Parameters.push_back(s_Parameter);
		}
	}

	return s_Parameters;
}