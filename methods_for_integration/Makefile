# copied and tweaked from: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR=headers
CC=cc
CFLAGS=-I$(IDIR) -Wall

ODIR=build

LIBS=-lm

_DEPS = equation.h riemann_sums.h
# tack on the include directory path
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = riemann_sums.o equation.o
# tack on the build path
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

riemann_sums: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	open -a Terminal .

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o