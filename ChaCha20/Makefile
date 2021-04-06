CC=gcc
CFLAGS=-W -Wall -O3 -I.
OE=.o
OUTE=
LFLAGS=-s

OBJECTS=chacha20$(OE) main$(OE)

.SUFFIXES: .c

%$(OE): %.c
	$(CC) $(CFLAGS) -o $@ -c $<

ALL: main$(OUTE)

main$(OUTE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LFLAGS)

clean:
	rm -f main$(OUTE) $(OBJECTS)
