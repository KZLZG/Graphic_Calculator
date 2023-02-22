CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: rebuild

rebuild: clean build

build: cipher

cipher:
	$(CC) $(CFLAGS)  cipher.c -o ../build/cipher

check:
	@echo ----------	
	@echo CPPCHECK:
	@cppcheck --enable=all --suppress=missingIncludeSystem .
	@echo ----------
	@echo
	@echo ----------
	@echo CODESTYLE:
	@cp ../materials/linters/CPPLINT.cfg .
	@python3 ../materials/linters/cpplint.py --extensions=c *.c */*.c */*.h
	@rm CPPLINT.cfg
	@echo ----------


clean:
	@rm -rf *.o *.so *out ../build/*
	clear

