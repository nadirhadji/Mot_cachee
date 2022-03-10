CC = gcc
EXEC = motcache
OPTION = -Wall -Wextra -std=c99
OBJ = solver.o file_handler.o main.o 

all: link

compile: $(OBJ)

main.o:	main.c
	$(CC) $(OPTION) -c %<

file_handler.o: file_handler.c file_handler.h 
	$(CC) $(OPTION) -c %<

solver.o: solver.c solver.h 
	$(CC) $(OPTION) -c %<

link: compile
	$(CC) *.o -o $(EXEC)

clean:
	rm *.o 
	rm $(EXEC)

test:

