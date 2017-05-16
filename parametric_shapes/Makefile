# copied and tweaked from: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR=headers
CC=cc

CFLAGS=-I$(IDIR) -Wall -L/usr/X11R6/lib -I../assignment_2/headers -Wall -g

ODIR=build

LIBS=-lm -lm -lX11 -lXext

_DEPS = GUI.h G_graphics.h X_graphics.h Non_graphics.h

# tack on the include directory path
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = GUI.o G_graphics.o X_graphics.o Non_graphics.o 
# tack on the build path
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

.DEFAULT_GOAL := cubic_splines

cubic_splines: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	./cubic_splines
	
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o