
# _____________________________________________________________________________
#
# file:         Makefile
# created:      Fri Jan 20 18:50:57 CET 2017
# by:           frank
#
# description:	
# _____________________________________________________________________________
#


CC      = gcc

CFLAGS  = `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0`


TARGETS	= cairo drawtest
TESTS	=
OBJ	=
DEP	= $(OBJ:.o=.d)

 
%.o:				%.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o:				%.cpp
	$(CC) -c $(CFLAGS) -o $@ $<


all:				$(TARGETS) $(TESTS)


cairo:			        cairo.o $(OBJ)
	$(CC) -o $@ $@.o $(OBJ) $(LDFLAGS)

drawtest:			drawtest.o $(OBJ)
	$(CC) -o $@ $@.o $(OBJ) $(LDFLAGS)


-include $(DEP)


clean:
	rm -f $(TARGETS) $(TESTS) *.o *.d

