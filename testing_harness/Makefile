# copied and tweaked from: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR=headers
CC=cc
CFLAGS=-I$(IDIR) -Wall

ODIR=build

LIBS=-lm

_DEPS = tester.h
# tack on the include directory path
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tester.o
# tack on the build path
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tester: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o