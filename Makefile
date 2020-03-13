
CC=g++

objects = functions.o maze.o

maze : $(objects)

$(objects) : maze.h

.PHONY: clean
clean:
	$(RM) maze *.o




