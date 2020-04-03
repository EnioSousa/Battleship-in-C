CC=gcc
CFLAGS=-I.
DEPS = game.h interface.h insert.h map.h ship.h
OBJ = game.o interface.o insert.o map.o ship.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

trab1: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o 
	rm game

run: 
	./game
