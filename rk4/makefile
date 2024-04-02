app.exe : main.o my_stack.o
	gcc -o app.exe main.o my_stack.o
    
main.o : main.c my_stack.h
	gcc -std=c99 -Wall -Werror -pedantic -c -o main.o main.c

my_stack.o : my_stack.c my_stack.h
	gcc -std=c99 -Wall -Werror -pedantic -c -o my_stack.o my_stack.c

.PHONY : clean

clean :
	rm -f *.o *.exe
