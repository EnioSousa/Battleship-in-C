CC=gcc
CFLAGS=-I. -Wall
DEPS = interface.h search.h insert.h errorMessage.h map.h point.h ship.h

ODIR=bin

_OBJ = test.o interface.o search.o insert.o errorMessage.o map.o ship.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS) 

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm $(ODIR)/*.o

