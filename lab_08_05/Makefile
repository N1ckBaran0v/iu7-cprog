# compiler
CC := gcc

# keys to compile
CKEYS := -std=c99 -Wall -Werror -pedantic

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
OBJS :=  ./out/my_io.o ./out/my_matrix.o ./out/my_multiple.o ./out/my_resize.o

# object files (unit tests)
UOBJS :=  ./out/check_main.o ./out/check_my_matrix.o ./out/check_my_multiple.o ./out/check_my_resize.o

# build app
app.exe : out/main.o $(OBJS)
	$(CC) -o app.exe ./out/main.o $(OBJS) $(LKEYS)

# build unit tests
unit_tests.exe : $(OBJS) $(UOBJS)
	$(CC) -o unit_tests.exe $(OBJS) $(UOBJS) -lrt -lcheck -lm

# compile ./out/main.o
./out/main.o: src/main.c inc/my_errors.h inc/my_matrix.h inc/my_resize.h inc/my_multiple.h inc/my_io.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/my_io.o
./out/my_io.o: src/my_io.c inc/my_io.h inc/my_matrix.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/my_matrix.o
./out/my_matrix.o: src/my_matrix.c inc/my_matrix.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/my_multiple.o
./out/my_multiple.o: src/my_multiple.c inc/my_multiple.h inc/my_matrix.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/my_resize.o
./out/my_resize.o: src/my_resize.c inc/my_resize.h inc/my_matrix.h inc/my_io.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_main.o
./out/check_main.o: unit_tests/check_main.c inc/check_my_matrix.h inc/check_my_multiple.h inc/check_my_resize.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_my_matrix.o
./out/check_my_matrix.o: unit_tests/check_my_matrix.c inc/check_my_matrix.h inc/my_matrix.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_my_multiple.o
./out/check_my_multiple.o: unit_tests/check_my_multiple.c inc/check_my_multiple.h inc/my_multiple.h inc/my_matrix.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_my_resize.o
./out/check_my_resize.o: unit_tests/check_my_resize.c inc/check_my_resize.h inc/my_resize.h inc/my_matrix.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# test program
func :
	./func_tests/scripts/func_tests.sh

# clean
.PHONY : clean debug release unit func
clean :
	$(RM) -f ./out/* ./*.exe ./func_tests/scripts/*.txt ./func_tests/scripts/*.log