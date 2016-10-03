CC = gcc
OBJECTS = smux.o format.o

smux : $(OBJECTS)
	$(CC) -o smux $(OBJECTS)

smux.o : smux.h format.h
format.o : format.h

.PHONY : clean
clean :
	-rm smux *.o
