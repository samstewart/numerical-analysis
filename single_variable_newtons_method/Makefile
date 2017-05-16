# copied and tweaked from: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR=headers
CC=cc
CFLAGS=-I$(IDIR) -Wall

ODIR=build

LIBS=-lm

_DEPS = complex_utility.h error_analysis.h polynomial.h synthetic_division.h newtons_guess_methods.h
# tack on the include directory path
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = error_analysis.o complex_utility.o polynomial.o synthetic_division.o newtons_approximator_polynomial.o newtons_guess_methods.o
# tack on the build path
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

newtons_method: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o