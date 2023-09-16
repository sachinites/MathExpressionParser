lex Parser.l
gcc -g -c lex.yy.c -o lex.yy.o
gcc -g -c MExpr.c -o MExpr.o
gcc -g -c stack/stack.c -o stack/stack.o
gcc -g MExpr.o lex.yy.o stack/stack.o -o exe -lfl -lm
# run the ./exe 
