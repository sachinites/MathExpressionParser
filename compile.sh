flex Parser.l
g++ -g -c -fpermissive lex.yy.c -o lex.yy.o
g++ -g -c -fpermissive MExpr.c -o MExpr.o
g++ -g -c -fpermissive ExpressionParser.c -o ExpressionParser.o
g++ -g -c -fpermissive ParserMexpr.c -o ParserMexpr.o
g++ -g -c -fpermissive test.c -o test.o
g++ -g test.o lex.yy.o ParserMexpr.o MExpr.o ExpressionParser.o -o exe -lfl -lm

#CPP files
g++ -g -c -fpermissive lex.yy.c -o lex.yy.o
g++ -g -c Operators.cpp -o Operators.o
g++ -g -c Dtype.cpp -o Dtype.o
g++ -g -c MexprTree.cpp -o MexprTree.o
g++ -g -c -fpermissive Cpptest.cpp -o Cpptest.o
g++ -g -c MexprEnumConvertor.cpp -o MexprEnumConvertor.o
g++ -g Operators.o Dtype.o MexprTree.o  lex.yy.o Cpptest.o MexprEnumConvertor.o ../RDBMSImplementation/core/SqlMexprIntf.o  ../RDBMSImplementation/core/sql_utils.o ../RDBMSImplementation/gluethread/glthread.o ../RDBMSImplementation/core/Catalog.o ExpressionParser.o ../RDBMSImplementation/BPlusTreeLib/BPlusTree.o -o cppexe -lm -lfl



