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
