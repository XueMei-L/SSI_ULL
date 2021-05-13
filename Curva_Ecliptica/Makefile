
main: main.o ecliptic.o
	g++ -g -o main main.o ecliptic.o

main.o: main.cpp
	g++ -g -c main.cpp

ecliptic.o: ecliptic.cpp
	g++ -g -c ecliptic.cpp

clean:
	rm *.o main