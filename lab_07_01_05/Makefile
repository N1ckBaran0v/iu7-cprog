# compiler
CC := gcc

# keys to compile
CKEYS := -std=c99 -Wall -Werror -pedantic

# keys to linking
LKEYS := -lm

# object files
OBJS := ./out/my_filter.o ./out/my_io.o ./out/my_sort.o

# object files (unit tests)
UOBJS := ./out/check_main.o ./out/check_my_filter.o ./out/check_my_io.o ./out/check_my_sort.o

# remove
RM := rm

debug : CKEYS += -g3 --coverage
debug : LKEYS += --coverage
debug : app.exe
release : CKEYS += -DNDEBUG -g0
release : app.exe
unit : unit_tests.exe
unit :
	./unit_tests.exe

# build app
app.exe : ./out/main.o ./out/my_filter.o ./out/my_io.o ./out/my_sort.o
	$(CC) -o app.exe $(OBJS) ./out/main.o $(LKEYS)

# built unit tests
unit_tests.exe : $(OBJS) $(UOBJS)
	$(CC) -o unit_tests.exe $(OBJS) $(UOBJS) -lrt -lcheck -lm

# compile ./out/check_main.o
./out/check_main.o : unit_tests/check_main.c inc/check_my_filter.h inc/check_my_io.h inc/check_my_sort.h inc/my_errors.h
	$(CC) $(CKEYS) -c ./unit_tests/check_main.c -o ./out/check_main.o

# compile ./out/check_my_filter.o
./out/check_my_filter.o : unit_tests/check_my_filter.c inc/check_my_filter.h inc/my_filter.h inc/my_errors.h
	$(CC) $(CKEYS) -c ./unit_tests/check_my_filter.c -o ./out/check_my_filter.o

# compile ./out/check_my_io.o
./out/check_my_io.o : unit_tests/check_my_io.c inc/check_my_io.h inc/my_io.h inc/my_errors.h
	$(CC) $(CKEYS) -c ./unit_tests/check_my_io.c -o ./out/check_my_io.o

# compile ./out/check_my_sort.o
./out/check_my_sort.o : unit_tests/check_my_sort.c inc/check_my_sort.h inc/my_sort.h
	$(CC) $(CKEYS) -c ./unit_tests/check_my_sort.c -o ./out/check_my_sort.o

# compile ./out/main.o
./out/main.o : src/main.c inc/my_errors.h inc/my_filter.h inc/my_sort.h inc/my_io.h
	$(CC) $(CKEYS) -c ./src/main.c -o ./out/main.o

# compile ./out/my_filter.o
./out/my_filter.o : src/my_filter.c inc/my_filter.h inc/my_errors.h
	$(CC) $(CKEYS) -c ./src/my_filter.c -o ./out/my_filter.o

# compile ./out/my_io.o
./out/my_io.o : src/my_io.c inc/my_io.h inc/my_errors.h
	$(CC) $(CKEYS) -c ./src/my_io.c -o ./out/my_io.o

# compile ./out/my_sort.o
./out/my_sort.o : src/my_sort.c inc/my_sort.h
	$(CC) $(CKEYS) -c ./src/my_sort.c -o ./out/my_sort.o

# test program
func :
	./func_tests/scripts/func_tests.sh

# clean
.PHONY : clean debug release unit func
clean :
	$(RM) -f ./out/* ./*.exe ./func_tests/scripts/*.txt ./func_tests/scripts/*.log