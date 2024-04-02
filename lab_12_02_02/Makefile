# compiler
CC := gcc

# keys to compile
CKEYS := -std=c99 -I ./inc/ -Wall -Werror -pedantic -fPIC

# remove
RM := rm

# compile ./out/libmyarr.so
./out/libmyarr.so: out/myarr.o
	$(CC) -o $@ -shared $<

# compile ./out/myarr.o
./out/myarr.o: src/myarr.c inc/myarr.h
	$(CC) $(CKEYS) -c $< -o $@

# clean
.PHONY : clean
clean :
	$(RM) -rf ./out/* __pycache__
