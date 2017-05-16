# copied and tweaked from: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR=headers
CC=gcc
CFLAGS=-I$(IDIR) -Wall -g

ODIR=build

LIBS=-lm

_DEPS = linear_solver.h matrix.h substitution.h LU_factorer.h
# tack on the include directory path
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = linear_solver.o matrix.o substitution.o LU_factorer.o
# tack on the build path
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

linear_solver: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

linear_solver_static: $(OBJ)
	ar rcs lib/liblinear_solver.a build/*.o

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o