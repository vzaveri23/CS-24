test: AST.o Nodes.o Stack.o test.o
	g++ AST.o Nodes.o Stack.o test.o -o test -Wall -Wextra -Werror -std=c++17

AST.o: AST.cpp
	g++ -c AST.cpp

Nodes.o: Nodes.cpp
	g++ -c Nodes.cpp

Stack.o: Stack.cpp
	g++ -c Stack.cpp

test.o: test.cpp
	g++ -c test.cpp

clean:
	rm -f *.o test

