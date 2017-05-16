# copied and tweaked from: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR=headers
CC=cc

CFLAGS=-I$(IDIR) -Wall -L/usr/X11R6/lib -I../assignment_2/headers -Wall -g -L../assignment_2/lib

ODIR=build

LIBS=-lm -lm -lX11 -lXext

_DEPS = GUI.h differential_equations.h G_graphics.h X_graphics.h Non_graphics.h

# tack on the include directory path
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = differential_equations.o GUI.o G_graphics.o X_graphics.o Non_graphics.o 
# tack on the build path
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

.DEFAULT_GOAL := run_differential_equation

differential_equation: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run_differential_equation: differential_equation
	./differential_equation

.PHONY: clean

clean:
	rm differential_equation
	rm -f $(ODIR)/*.o