
main: main.o diffie_hellman_elgamal.o
	g++ -g -o main main.o diffie_hellman_elgamal.o

main.o: main.cpp
	g++ -g -c main.cpp

diffie_hellman_elgamal.o: diffie_hellman_elgamal.cpp
	g++ -g -c diffie_hellman_elgamal.cpp

clean:
	rm *.o main