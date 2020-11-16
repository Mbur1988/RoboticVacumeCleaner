FLAGS=-std=gnu99 -Wall -Werror -g
ZDK_LIB=-L../ZDK -lzdk -lncurses
OBJ=main.o helpers.o my_helpers.o setup.o operation.o status.o input.o

default: all

helpers.o: helpers.c
	gcc -c helpers.c $(FLAGS) -I../ZDK
	
my_helpers.o: my_helpers.c
	gcc -c my_helpers.c $(FLAGS) -I../ZDK
	
setup.o: setup.c
	gcc -c setup.c $(FLAGS) -I../ZDK

operation.o: operation.c
	gcc -c operation.c $(FLAGS) -I../ZDK
	
status.o: status.c
	gcc -c status.c $(FLAGS) -I../ZDK
	
input.o: input.c
	gcc -c input.c $(FLAGS) -I../ZDK
	
main.o: main.c
	gcc -c main.c $(FLAGS) -I../ZDK
	
all: $(OBJ)
	gcc $(OBJ) $(FLAGS) $(ZDK_LIB) -lm -o Vacuum
	rm $(OBJ)
