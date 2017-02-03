#include <Misc/StdAfx.h>

#include <Parser/ParserTree.h>

#include <Managers/CodeManager.h>

extern int yyparse();
extern int yylex();

extern int yydebug;
extern FILE* yyin;

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	//yydebug = 1;

	// TODO: Remove this.
	argc = 2;
	char* s_TempArgs[] = { argv[0], "test.opcl" };
	argv = s_TempArgs;
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

	Parser::ParserTree::GetProgram()->Generate();

	printf("\n");
	printf(Managers::CodeManager::Writer()->GetBuffer().c_str());

	// Close the file.
	fclose(yyin);
	yyin = nullptr;

	getchar();

    return 0;
}

void yyerror(const char* p_Error) 
{ 
	printf("Error: %s\n", p_Error); 
}
