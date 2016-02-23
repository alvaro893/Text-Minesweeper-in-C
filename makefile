CC=gcc
CFLAGS=-I.
DEPS=table.h
OBJ=table.o testProgram.o

all: mines

mines: $(OBJ)
	$(CC) -o mines $(OBJ)
	
testProgram.o: testProgram.c $(DEPS)
	$(CC) -c testProgram.c

table.o: table.c $(DEPS)
	$(CC) -c table.c $(CFLAGS)

clean:
	rm $(OBJ) mines
