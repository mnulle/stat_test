all: test

test: Stats.o test.o
	g++ test.o Stats.o -o test

test.o: test.cpp
	g++ -c test.cpp

Stats.o:
	g++ -c Stats.cc

clean:
	rm *.o *~ test
