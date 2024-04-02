# compiler
CC := gcc

# keys to compile
CKEYS := -std=gnu99 -I ./inc/ -Wall -Werror

# keys to linking
LKEYS := -lm

# remove
RM := rm

# build debug
debug : CKEYS += -g3
debug : app.exe

# build release
release : CKEYS += -DNDEBUG -g0
release : app.exe

# build unit tests
unit : unit_tests.exe
	./unit_tests.exe

# object files
OBJS :=  ./out/my_filter.o ./out/my_io.o ./out/my_sort.o

# object files (unit tests)
UOBJS :=  ./out/check_main.o ./out/check_my_filter.o ./out/check_my_io.o ./out/check_my_sort.o

# libraries
LIBS := 

# library link keys
LLKEYS :=

ifeq ($(libmode), static)
	LIBS += ./out/libsort.a
	LLKEYS += -L./out -lsort
endif

ifeq ($(libmode), dyncomp)
	LIBS += ./out/libsort.so
	CKEYS += -fPIC
	LLKEYS += -L./out -lsort
endif

ifeq ($(libmode), dynlink)
	LIBS += ./out/libsort.so
	CKEYS += -fPIC -DDYN_LOAD
endif

# build app
app.exe : out/main.o $(LIBS)
	$(CC) -o app.exe ./out/main.o $(LKEYS) $(LLKEYS)

# build unit tests
unit_tests.exe : $(LIBS) $(UOBJS)
	$(CC) -o unit_tests.exe $(UOBJS) -lrt -lcheck  -lsubunit $(LKEYS) $(LLKEYS)

# build libsort.a
./out/libsort.a : $(OBJS)
	ar cr $@ $(OBJS)

# build libsort.so
./out/libsort.so : $(OBJS)
	$(CC) -o $@ -shared $(OBJS)

# compile ./out/main.o
./out/main.o: src/main.c inc/my_errors.h inc/my_filter.h inc/my_sort.h inc/my_io.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/my_filter.o
./out/my_filter.o: src/my_filter.c inc/my_filter.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/my_io.o
./out/my_io.o: src/my_io.c inc/my_io.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/my_sort.o
./out/my_sort.o: src/my_sort.c inc/my_sort.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_main.o
./out/check_main.o: unit_tests/check_main.c inc/my_errors.h inc/check_my_filter.h inc/check_my_io.h inc/check_my_sort.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_my_filter.o
./out/check_my_filter.o: unit_tests/check_my_filter.c inc/check_my_filter.h inc/my_filter.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_my_io.o
./out/check_my_io.o: unit_tests/check_my_io.c inc/check_my_io.h inc/my_io.h inc/my_errors.h
	$(CC) $(CKEYS) -c $< -o $@

# compile ./out/check_my_sort.o
./out/check_my_sort.o: unit_tests/check_my_sort.c inc/check_my_sort.h inc/my_sort.h
	$(CC) $(CKEYS) -c $< -o $@

# test program
func :
	./func_tests/scripts/func_tests.sh

# clean
.PHONY : clean debug release unit func
clean :
	$(RM) -f ./out/* ./*.exe ./func_tests/scripts/*.txt ./func_tests/scripts/*.log