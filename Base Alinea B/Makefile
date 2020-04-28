CC=gcc
CFLAGS=-I. -Wall
DEPS = point.h error.h ship.h map.h search.h insert.h object.h listObj.h debbug.h delete.h

ODIR=bin

_OBJ = test.o error.o point.o ship.o map.o search.o insert.o object.o listObj.o debbug.o delete.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS) 

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm $(ODIR)/*.o
