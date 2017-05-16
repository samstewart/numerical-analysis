# copied and tweaked from: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR=headers
CC=cc

CFLAGS=-I$(IDIR) -Wall -L/usr/X11R6/lib -I../linear_system_solver/headers -Wall -g -L../linear_system_solver/lib -llinear_solver

ODIR=build

LIBS=-lm -lm -lX11 -lXext

_DEPS = GUI.h comprehensive_interpolation.h G_graphics.h X_graphics.h Non_graphics.h

# tack on the include directory path
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = comprehensive_interpolation.o GUI.o G_graphics.o X_graphics.o Non_graphics.o 
# tack on the build path
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

.DEFAULT_GOAL := comprehensive_interpolation

comprehensive_interpolation: $(OBJ)
	# rebuild the linear solver library
	make -C ../linear_system_solver clean
	make -C ../linear_system_solver linear_solver_static
	
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	./comprehensive_interpolation
	
.PHONY: clean

clean:
	rm comprehensive_interpolation
	rm -f $(ODIR)/*.o
	rm -f ../linear_system_solver/lib/*.a