rm -f  libMexp.a
rm *.o
g++ -g -c -fpermissive ExpressionParser.c -o ExpressionParser.o
g++ -g -c Operators.cpp -o Operators.o
g++ -g -c Dtype.cpp -o Dtype.o
g++ -g -c MexprTree.cpp -o MexprTree.o
g++ -g -c EnumConvertor.cpp -o EnumConvertor.o
g++ -g -c Aggregators.cpp -o Aggregators.o
ar rcs libMexp.a ExpressionParser.o Operators.o Dtype.o MexprTree.o Aggregators.o EnumConvertor.o
