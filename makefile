P=oposim
CFLAGS=-I$(HOME)/root/include -g -O3 -Wall -std=gnu11
LDLIBS=-L$(HOME)/root/lib `pkg-config --libs gsl`
OBJECTS=ops_parser.o oposim_fns.o
CC=gcc
DOCGEN=doxygen

$(P): $(OBJECTS)

oposim_fns.o:
	$(CC) $(CFLAGS) -c -o oposim_fns.o  oposim_fns.c $(LDLIBS)

clean: clean-o clean-exe clean-tmp

clean-o:
	rm -f *.o

clean-exe:
	rm -f *.exe $(P)

clean-tmp:
	rm -f *~ \#*

doc:
	$(DOCGEN) && firefox ./html/index.html &
