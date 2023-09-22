lex Parser.l
gcc -g -c lex.yy.c -o lex.yy.o
gcc -g -c MExpr.c -o MExpr.o
gcc -g -c ExpressionParser.c -o ExpressionParser.o
gcc -g -c ParserMexpr.c -o ParserMexpr.o
gcc -g -c test.c -o test.o
gcc -g test.o lex.yy.o ParserMexpr.o MExpr.o ExpressionParser.o -o exe -lfl -lm

