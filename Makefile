CC=gcc
CFLAGS=-I.
DEPS = point.h error.h ship.h interface.h map.h insertDelete.h input.h player.h game.h clearMemory.h playGame.h
OBJ = point.o error.o ship.o interface.o map.o insertDelete.o input.o player.o  game.o clearMemory.o playGame.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

trab1: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o 
	rm game

run: 
	./game
