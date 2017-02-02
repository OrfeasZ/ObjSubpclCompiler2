%{
#include <stdio.h>
#include <string>
#include <Parser/ParserTree.h>
#include "grammar.tab.hpp"

extern "C" int yywrap();
extern void yyerror(const char* err);
%}

%x COMMENT

newline					(\r?\n)
digit					[0-9]
white_space				[ \t]*
alpha 					[A-Za-z]
alpha_num				({alpha}|{digit})

id						{alpha}{alpha_num}*
unsigned_integer		{digit}+

%%

"/*"					BEGIN(COMMENT);
<COMMENT>[^/*\n]+
<COMMENT>\n				
<COMMENT><<EOF>>		yyerror("EOF in comment");
<COMMENT>"*/"			BEGIN(INITIAL);
<COMMENT>[*/]

and						return(AND);
array 					return(ARRAY);
begin 					return(BEGINT);
div						return(DIV);
do 						return(DO);
else 					return(ELSE);
end 					return(END);
if 						return(IF);
integer 				return(INTEGER);
mod 					return(MOD);
not 					return(NOT);
of 						return(OF);
or 						return(OR);
procedure 				return(PROCEDURE);
program 				return(PROGRAM);
real 					return(REAL);
return 					return(RETURN);
then 					return(THEN);
var 					return(VAR);
while 					return(WHILE);
class					return(CLASS);
extends					return(EXTENDS);
constructor				return(CONSTRUCTOR);
abstract				return(ABSTRACT);
dynamic					return(DYNAMIC);

"("						return(LPAREN);
")"						return(RPAREN);
"*"						return(STAR);
"+"						return(PLUS);
","						return(COMMA);
"-"						return(MINUS);
"."						return(DOT);
"/"						return(SLASH);
":"						return(COLON);
":="					return(ASSIGN);
";"						return(SEMICOLON);
"<"						return(LT);
"<="					return(LTE);
"<>"					return(NOTEQUAL);
"="						return(EQUAL);
">"						return(GT);
">="					return(GTE);
"["						return(LBRACK);
"]"						return(RBRACK);

{unsigned_integer}		yylval.string = new std::string(yytext, yyleng); return(UNSIGNED_INTEGER);
{id}					yylval.string = new std::string(yytext, yyleng); return(IDENTIFIER);

{white_space}			/* nothing */
{newline}				
.						yyerror("Illegal input");

%%
