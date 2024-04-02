# compiler
CC := gcc

# keys to compile
CKEYS := -std=gnu99 -I ./inc/ -Wall -Werror -pedantic

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
OBJS :=  ./out/my_snprintf.o

# object files (unit tests)
UOBJS :=  ./out/check_main.o ./out/check_my_snprintf.o

# build app
app.exe : out/main.o $(OBJS)
	$(CC) -o app.exe ./out/main.o $(OBJS) $(LKEYS)

# build unit tests
unit_tests.exe : $(OBJS) $(UOBJS)
	$(CC) -o unit_tests.exe $(OBJS) $(UOBJS) -lrt -lcheck -lm

# compile ./out/main.o
./out/main.o: src/main.c
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/my_snprintf.o
./out/my_snprintf.o: src/my_snprintf.c inc/my_snprintf.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_main.o
./out/check_main.o: unit_tests/check_main.c inc/check_my_snprintf.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_my_snprintf.o
./out/check_my_snprintf.o: unit_tests/check_my_snprintf.c inc/check_my_snprintf.h inc/my_snprintf.h
	$(CC) $(CKEYS) -c $< -o $@

# clean
.PHONY : clean debug release unit
clean :
	$(RM) -f ./out/* ./*.exe
