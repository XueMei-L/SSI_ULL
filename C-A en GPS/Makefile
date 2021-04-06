main: main.o cagps.o
	g++ -o main main.o cagps.o

main.o: main.cpp
	g++ -c main.cpp

cagps.o: cagps.cpp
	g++ -c cagps.cpp

clean:
	rm *.o main