CC = gcc
OBJECTS = smux.o graphics.o format.o

smux : $(OBJECTS)
	$(CC) -o smux $(OBJECTS)

smux.o : smux.h graphics.h format.h
graphics.o: graphics.h
format.o : format.h

.PHONY : clean
clean :
	-rm smux *.o
