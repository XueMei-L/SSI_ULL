CC=gcc
CFLAGS=-Wall -O2

main: aes.o main.o
	$(CC) -g -o $@ $^ $(CFLAGS)

clean:
	rm *.o main
