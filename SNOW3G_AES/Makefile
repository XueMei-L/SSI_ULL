main: main.o snow3gyaes.o
	g++ -g -o main main.o snow3gyaes.o

main.o: main.cpp
	g++ -g -c main.cpp

snow3gyaes.o: snow3gyaes.cpp
	g++ -g -c snow3gyaes.cpp

clean:
	rm *.o main