
# _____________________________________________________________________________
#
# file:         Makefile
# created:      Fri Jan 20 18:50:57 CET 2017
# by:           frank
#
# description:	
# _____________________________________________________________________________
#


CC      = g++

CFLAGS  = `pkg-config --cflags gtkmm-3.0`
LDFLAGS = `pkg-config --libs gtkmm-3.0`


TARGETS	= myarea
TESTS	=
OBJ	= myarea.o
DEP	= $(OBJ:.o=.d)

 
%.o:				%.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o:				%.cc
	$(CC) -c $(CFLAGS) -o $@ $<


all:				$(TARGETS) $(TESTS)


myarea:		        main.o $(OBJ)
	$(CC) -o $@ main.o $(OBJ) $(LDFLAGS)



-include $(DEP)


clean:
	rm -f $(TARGETS) $(TESTS) *.o *.d

