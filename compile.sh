
g++ -g -c -fpermissive ExpressionParser.c -o ExpressionParser.o
g++ -g -c Operators.cpp -o Operators.o
g++ -g -c Dtype.cpp -o Dtype.o
g++ -g -c MexprTree.cpp -o MexprTree.o
g++ -g -c EnumConvertor.cpp -o EnumConvertor.o
g++ -g -c ../RDBMSImplementation/core/SqlMexprIntf.cpp -o ../RDBMSImplementation/core/SqlMexprIntf.o
ar rcs libMexp.a ExpressionParser.o Operators.o Dtype.o MexprTree.o EnumConvertor.o ../RDBMSImplementation/core/SqlMexprIntf.o

#Create Executable
#flex Parser.l
#g++ -g -c -fpermissive lex.yy.c -o lex.yy.o
#g++ -g -c -fpermissive Cpptest.cpp -o Cpptest.o
#g++ -g Operators.o Dtype.o MexprTree.o  lex.yy.o Cpptest.o EnumConvertor.o ../RDBMSImplementation/core/SqlMexprIntf.o  ../RDBMSImplementation/core/sql_utils.o ../RDBMSImplementation/gluethread/glthread.o ../RDBMSImplementation/core/Catalog.o ExpressionParser.o ../RDBMSImplementation/BPlusTreeLib/BPlusTree.o -o cppexe -lm -lfl
