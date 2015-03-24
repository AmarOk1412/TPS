CC=g++
CFLAGS=-Wall -I../include
CLIBS=
LDFLAGS=
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
EXEC=../TP13
DEBUGDIR=../Debug

all: objects
	$(CC) $(LDFLAGS) $(OBJ) -o $(EXEC) $(CLIBS) 2> errorlog

objects:
	$(CC) $(CFLAGS) -c $(SRC) 2> errorlog

debug: prod
	valgrind --leak-check=full $(EXEC) 2> errorlog

prod: clean all

.PHONY: clean mrproper

clean:
	rm -rf *.o
	rm -rf $(EXEC)
	rm -rf *~

