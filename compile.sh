lex Parser.l
gcc -g -c lex.yy.c -o lex.yy.o
gcc -g -c MExpr.c -o MExpr.o
gcc -g -c ExpressionParser.c -o ExpressionParser.o
gcc -g -c ParserMexpr.c -o ParserMexpr.o
gcc -g -c testInternal.c -o testInternal.o
ar rs libMexpr.a lex.yy.o MExpr.o ExpressionParser.o
gcc -g testInternal.o -o exe -L . -lMexpr -lfl -lm

# run the ./exe 
