IDIR =../inc
CC=gcc
CFLAGS= -I$(IDIR) -Wall -pedantic -g

ODIR=../obj
LDIR =../lib

LIBS=-lm

_DEPS = PGMimage.h PPMimage.h Utils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
#        ^^^^^^^^
#   Performs a textual replacement on the text text: each occurrence of from is replaced by to.
#   The result is substituted for the function call.

_OBJ = main.o PGMimage.o PPMimage.o Utils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

__start__: ../image_processing
	../image_processing

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

../image_processing: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ ../image_processing

debug:
	gdb ./image_processing