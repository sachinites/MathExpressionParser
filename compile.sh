flex Parser.l
g++ -g -c -fpermissive lex.yy.c -o lex.yy.o
g++ -g -c -fpermissive MExpr.c -o MExpr.o
g++ -g -c -fpermissive ExpressionParser.c -o ExpressionParser.o
g++ -g -c -fpermissive ParserMexpr.c -o ParserMexpr.o
g++ -g -c -fpermissive test.c -o test.o

#CPP files
g++ -g -c Operators.cpp -o Operators.o
g++ -g -c Dtype.cpp -o Dtype.o
g++ -g -c MexprTree.cpp -o MexprTree.o
g++ -g -c Cpptest.cpp -o Cpptest.o
g++ -g -c MexprEnumConvertor.cpp -o MexprEnumConvertor.o
g++ -g Operators.o Dtype.o MexprTree.o Cpptest.o MexprEnumConvertor.o -o cppexe

g++ -g test.o lex.yy.o ParserMexpr.o MExpr.o ExpressionParser.o -o exe -lfl -lm

