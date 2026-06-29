CC = gcc
CFLAGS = -Wall -g

all: sistema

sistema: main.o usuarios.o productos.o
	$(CC) $(CFLAGS) -o sistema main.o usuarios.o productos.o

main.o: main.c usuarios.h productos.h
	$(CC) $(CFLAGS) -c main.c

usuarios.o: usuarios.c usuarios.h
	$(CC) $(CFLAGS) -c usuarios.c

productos.o: productos.c productos.h
	$(CC) $(CFLAGS) -c productos.c

clean:
	rm -f *.o sistema
