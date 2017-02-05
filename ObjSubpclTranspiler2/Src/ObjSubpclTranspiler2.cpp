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

#include <Misc/StdAfx.h>

#include <Parser/ParserTree.h>

#include <Managers/CodeManager.h>

#include <fstream>

extern int yyparse();
extern int yylex();

extern int yydebug;
extern FILE* yyin;

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	yydebug = 1;
#endif

	if (argc != 2)
	{
		printf("Usage: ObjSubpclTranspiler2 [file]\n");
		return 1;
	}

	yyin = fopen(argv[1], "r");

	if (yyin == nullptr)
	{
		printf("Failed to open input file '%s'.\n", argv[1]);
		return 1;
	}

	printf("Parsing file. Please wait.\n");

	yyparse();
	
	printf("Finished parsing file.\n");

	if (!Parser::ParserTree::GetProgram())
	{
		printf("Tree generation failed.\n");
		return 1;
	}

	printf("Transpiling code...\n");

	try
	{
		Parser::ParserTree::GetProgram()->Generate();
	}
	catch (std::exception& ex)
	{
		printf("Code generation failed with error:\n");
		printf(ex.what());
		printf("\n");
		return 1;
	}
	
	printf("Transpilation finished!\n");

	std::ofstream s_SourceFile(std::string(argv[1]) + ".c", std::ofstream::out);
	s_SourceFile << Managers::CodeManager::Writer()->GetBuffer();
	s_SourceFile.flush();
	s_SourceFile.close();

	// Close the file.
	fclose(yyin);
	yyin = nullptr;

    return 0;
}

void yyerror(const char* p_Error) 
{ 
	printf("Error: %s\n", p_Error); 
}
