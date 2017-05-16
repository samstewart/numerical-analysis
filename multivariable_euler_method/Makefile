# copied and tweaked from: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR=headers
CC=gcc
# we need to statically link with our linear solver
CFLAGS=-I$(IDIR) -I../assignment_2/headers -Wall -g -L../assignment_2/lib -llinear_solver

.DEFAULT_GOAL := multivariable_newtons
ODIR=build

LIBS=-lm

_DEPS = equation.h fixed_point.h newtons_multivariable.h
# tack on the include directory path
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# make certain to link directly with the library
_OBJ = equation.o fixed_point.o newtons_multivariable.o

# tack on the build path
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# make sure to link with our static library
multivariable_newtons: $(OBJ)
	# rebuild the linear solver library
	make -C ../assignment_2 clean
	make -C ../assignment_2 linear_solver_static

	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f multivariable_newtons
	rm -f $(ODIR)/*.o
	rm -f ../assignment_2/lib/*.a