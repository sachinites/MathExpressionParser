lex Parser.l
g++ -g -c lex.yy.c -o lex.yy.o
g++ -g -c ExpressionParser.c -o ExpressionParser.o
g++ -g -c SqlSelectParserCFG.c -o SqlSelectParserCFG.o
g++ -g lex.yy.o ExpressionParser.o SqlSelectParserCFG.o -o exe -lfl
