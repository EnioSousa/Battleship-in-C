CC=gcc
CFLAGS=-I. -Wall
DEPS = error.h insertDelete.h interface.h map.h point.h ship.h

ODIR=bin

_OBJ = test.o error.o insertDelete.o interface.o map.o ship.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS) 

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm $(ODIR)/*.o

