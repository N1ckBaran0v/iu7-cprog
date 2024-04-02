# compiler
CC := gcc

# keys to compile
CKEYS := -std=c99 -I ./inc/ -Wall -Werror -pedantic

# keys to linking
LKEYS := -lm

# remove
RM := rm

# build debug
debug : CKEYS += -g3 --coverage
debug : LKEYS += --coverage
debug : app.exe

# build release
release : CKEYS += -DNDEBUG -g0
release : app.exe

# build unit tests
unit : unit_tests.exe
	./unit_tests.exe

# object files
OBJS :=  ./out/my_find.o ./out/my_io.o ./out/my_memory.o

# object files (unit tests)
UOBJS :=  ./out/check_main.o ./out/check_my_find.o ./out/check_my_io.o

# build app
app.exe : out/main.o $(OBJS)
	$(CC) -o app.exe ./out/main.o $(OBJS) $(LKEYS)

# build unit tests
unit_tests.exe : $(OBJS) $(UOBJS)
	$(CC) -o unit_tests.exe $(OBJS) $(UOBJS) -lrt -lcheck -lm

# compile ./out/main.o
./out/main.o: src/main.c inc/my_errors.h inc/my_memory.h inc/my_struct.h inc/my_find.h inc/my_io.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/my_find.o
./out/my_find.o: src/my_find.c inc/my_struct.h inc/my_errors.h inc/my_find.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/my_io.o
./out/my_io.o: src/my_io.c inc/my_io.h inc/my_struct.h inc/my_errors.h inc/my_memory.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/my_memory.o
./out/my_memory.o: src/my_memory.c inc/my_memory.h inc/my_struct.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_main.o
./out/check_main.o: unit_tests/check_main.c inc/check_my_find.h inc/my_find.h inc/my_struct.h inc/check_my_io.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_my_find.o
./out/check_my_find.o: unit_tests/check_my_find.c inc/check_my_find.h inc/my_find.h inc/my_struct.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_my_io.o
./out/check_my_io.o: unit_tests/check_my_io.c inc/check_my_io.h inc/my_io.h inc/my_struct.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# test program
func :
	./func_tests/scripts/func_tests.sh

# clean
.PHONY : clean debug release unit func
clean :
	$(RM) -f ./out/* ./*.exe ./func_tests/scripts/*.txt ./func_tests/scripts/*.log
