CC=gcc
CFLAGS=-I. -Wall
DEPS = interface.h search.h insert.h errorMessage.h map.h point.h ship.h clearMemory.h input.h player.h playGame.h game.h

ODIR=bin

_OBJ = interface.o search.o insert.o errorMessage.o map.o point.o ship.o clearMemory.o input.o player.o playGame.o game.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS) 

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm $(ODIR)/*.o

