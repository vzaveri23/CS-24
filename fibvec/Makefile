test: test.o FibVec.o
	g++ test.o FibVec.o -o test

test.o: test.cpp
	g++ -c test.cpp

FibVec.o: FibVec.cpp
	g++ -c FibVec.cpp

clean:
	rm -f *.o test