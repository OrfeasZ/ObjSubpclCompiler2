#include <Misc/StdAfx.h>

extern int yyparse();
extern int yylex();

extern int yydebug;
extern FILE* yyin;

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	yydebug = 1;

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

	// Close the file.
	fclose(yyin);
	yyin = nullptr;

    return 0;
}

void yyerror(const char* p_Error) 
{ 
	printf("Error: %s\n", p_Error); 
}