test: test.o Node.o Set.o
	g++ -g test.o Node.o Set.o -o test -Wall -Wextra -Werror -std=c++17

test.o: test.cpp
	g++ -g -c test.cpp 

Node.o: Node.cpp
	g++ -g -c Node.cpp

Set.o: Set.cpp
	g++ -g -c Set.cpp

clean:
	rm -f *.o test