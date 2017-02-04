#include "ReturnStatement.h"

#include <Managers/CodeManager.h>

using namespace Parser;

ReturnStatement::ReturnStatement()
{
}

void ReturnStatement::Generate()
{
	Managers::CodeManager::Writer()->Write("return");
}