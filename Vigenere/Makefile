main: main.o cv.o
	g++ -o main main.o cv.o

main.o: main.cpp
	g++ -c main.cpp

cv.o: cv.cpp
	g++ -c cv.cpp

clean:
	rm *.o main