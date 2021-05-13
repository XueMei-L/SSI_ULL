main: main.o rsa.o
	g++ -g -o main main.o rsa.o

main.o: main.cpp
	g++ -g -c main.cpp

rsa.o: rsa.cpp
	g++ -g -c rsa.cpp

clean:
	rm *.o main