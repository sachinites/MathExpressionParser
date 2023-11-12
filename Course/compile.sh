rm -f *.o
rm -f *exe
lex Parser.l
g++ -g -c lex.yy.c -o lex.yy.o
g++ -g -c ExpressionParser.c -o ExpressionParser.o
g++ -g -c SqlSelectParserCFG.c -o SqlSelectParserCFG.o
g++ -g -c EnumConvertor.cpp -o EnumConvertor.o
g++ -g lex.yy.o ExpressionParser.o SqlSelectParserCFG.o EnumConvertor.o -o exe -lfl
g++ -g -c infix_to_postfix_test.c -o infix_to_postfix_test.o
g++ -g -c MexprTree.cpp -o MexprTree.o
g++ -g -c Operators.cpp -o Operators.o
g++ -g -c Dtype.cpp -o Dtype.o
g++ -g -c calculator.cpp -o calculator.o
g++ -g infix_to_postfix_test.o MexprTree.o Operators.o Dtype.o -o infix_to_postfix_test.exe
g++ -g lex.yy.o calculator.o EnumConvertor.o ExpressionParser.o MexprTree.o Operators.o Dtype.o -o calculator.exe -lfl
ar rcs libMexpr.a ExpressionParser.o Operators.o Dtype.o MexprTree.o EnumConvertor.o
