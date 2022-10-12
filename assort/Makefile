test: test.o List.o
	g++ test.o List.o -o test -Wall -Wextra -Werror -std=c++17

test.o: test.cpp
	g++ -c test.cpp

List.o: List.cpp
	g++ -c List.cpp

clean:
	rm -f *.o test
