CC=gcc
CFLAGS=-I. -Wall
DEPS = errorMessage.h point.h ship.h map.h search.h insert.h interface.h mapLinkedList.h delete.h player.h input.h clearMemory.h playGame.h game.h

ODIR=./bin

_OBJ = errorMessage.o point.o ship.o map.o search.o insert.o interface.o mapLinkedList.o delete.o player.o input.o clearMemory.o playGame.o game.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS) 

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm $(ODIR)/*.o

