flex Parser.l
g++ -g -c -fpermissive lex.yy.c -o lex.yy.o
g++ -g -c -fpermissive MExpr.c -o MExpr.o
g++ -g -c -fpermissive ExpressionParser.c -o ExpressionParser.o
g++ -g -c -fpermissive ParserMexpr.c -o ParserMexpr.o
g++ -g -c -fpermissive test.c -o test.o
g++ -g test.o lex.yy.o ParserMexpr.o MExpr.o ExpressionParser.o -o exe -lfl -lm

