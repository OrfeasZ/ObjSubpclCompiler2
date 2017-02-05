LEX = flex -olex.yy.cpp
YACC = bison -d
CC=g++
CFLAGS=-g -c -std=c++11 -ISrc
LDFLAGS=-lfl -ly
SOURCES=Src/Grammar/grammar.tab.cpp Src/Grammar/lex.yy.cpp Src/Managers/ClassManager.cpp Src/Managers/CodeManager.cpp Src/ObjSubpclTranspiler2.cpp Src/Parser/ArrayVariableType.cpp Src/Parser/Body.cpp Src/Parser/Class/ClassBody.cpp Src/Parser/Class/ClassDefinition.cpp Src/Parser/Class/ClassHeader.cpp Src/Parser/Class/ClassVariablePointerType.cpp Src/Parser/Class/ClassVariableType.cpp Src/Parser/Expressions/ArrayExpression.cpp Src/Parser/Expressions/BinaryExpression.cpp Src/Parser/Expressions/Call.cpp Src/Parser/Expressions/IDExpression.cpp Src/Parser/Expressions/Integer.cpp Src/Parser/Expressions/MemberCall.cpp Src/Parser/Expressions/MemberValue.cpp Src/Parser/Expressions/Real.cpp Src/Parser/Expressions/UnaryExpression.cpp Src/Parser/Identifier.cpp Src/Parser/ParserTree.cpp Src/Parser/Procedure/Procedure.cpp Src/Parser/Procedure/ProcedureBody.cpp Src/Parser/Procedure/ProcedureHeader.cpp Src/Parser/Program.cpp Src/Parser/Statements/AssignmentStatement.cpp Src/Parser/Statements/IfStatement.cpp Src/Parser/Statements/NewStatement.cpp Src/Parser/Statements/ReturnStatement.cpp Src/Parser/Statements/WhileStatement.cpp Src/Parser/VariableDeclaration.cpp Src/Parser/VariableType.cpp Src/Util/CodeWriter.cpp Src/Util/Utils.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ObjSubpclTranspiler2
PARSER=Src/Grammar/grammar.tab.cpp Src/Grammar/grammar.tab.hpp
LEXER=Src/Grammar/lex.yy.cpp

all: $(PARSER) $(LEXER) $(SOURCES) $(EXECUTABLE)

$(PARSER): Src/Grammar/grammar.ypp
	cd Src/Grammar && $(YACC) grammar.ypp

$(LEXER): Src/Grammar/grammar.lex
	cd Src/Grammar && $(LEX) grammar.lex

$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -rf $(PARSER) $(LEXER) $(OBJECTS) $(EXECUTABLE)