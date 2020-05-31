CC=gcc
CFLAGS=-I. -Wall
DEPS = engine.h errorMessage.h point.h ship.h map.h search.h insert.h interface.h mapLinkedList.h delete.h input.h player.h

ODIR=./bin

_OBJ = engine.o errorMessage.o point.o ship.o map.o search.o insert.o interface.o mapLinkedList.o delete.o input.o player.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

all: main client server

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

client:
	$(CC) -o client client.c $(CFLAGS)

server:
	$(CC) -o server server.c $(CFLAGS)

clean:
	rm $(ODIR)/*.o
	rm ./server
	rm ./client
	rm ./main
