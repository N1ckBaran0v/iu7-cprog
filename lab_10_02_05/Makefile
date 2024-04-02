# compiler
CC := gcc

# keys to compile
CKEYS := -std=gnu99 -I ./inc/ -Wall -Werror -pedantic
 
# keys to linking
LKEYS := -lm

# remove
RM := rm

# build debug
debug : CKEYS += -O0 -g3 --coverage
debug : LKEYS += --coverage
debug : app.exe

# build release
release : CKEYS += -DNDEBUG -g0
release : app.exe

# build unit tests
unit : unit_tests.exe
	./unit_tests.exe

# object files
OBJS :=  ./out/my_list.o

# object files (unit tests)
UOBJS :=  ./out/check_main.o ./out/check_my_list.o

# build app
app.exe : out/main.o $(OBJS)
	$(CC) -o app.exe ./out/main.o $(OBJS) $(LKEYS)

# build unit tests
unit_tests.exe : $(OBJS) $(UOBJS)
	$(CC) -o unit_tests.exe $(OBJS) $(UOBJS) -lrt -lcheck -lm

# compile ./out/main.o
./out/main.o: src/main.c inc/my_errors.h inc/my_list.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/my_list.o
./out/my_list.o: src/my_list.c inc/my_list.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_main.o
./out/check_main.o: unit_tests/check_main.c inc/check_my_list.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_my_list.o
./out/check_my_list.o: unit_tests/check_my_list.c inc/check_my_list.h inc/my_list.h
	$(CC) $(CKEYS) -c $< -o $@

# test program
func :
	./func_tests/scripts/func_tests.sh

# clean
.PHONY : clean debug release unit func
clean :
	$(RM) -f ./out/* ./*.exe ./func_tests/scripts/*.txt ./func_tests/scripts/*.log
