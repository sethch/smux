CC = gcc
OBJECTS = smux.o graphics.o format.o

smux : $(OBJECTS)
	$(CC) $(OBJECTS) -lutil -l c -pthread -ggdb -o smux -lncurses

smux.o : smux.h graphics.h format.h
graphics.o: graphics.h
format.o : format.h

.PHONY : clean
clean :
	-rm *.o
