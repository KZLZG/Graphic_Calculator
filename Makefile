CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: rebuild

rebuild: clean build

build: io_module.o calc_module.o parser.o stack.o
	$(CC) $(CFLAGS) $^ graph.c -o ../build/graph


io_module.o:
	$(CC) $(CFLAGS) -c ./io_module/io_module.c

calc_module.o:
	$(CC) $(CFLAGS) -c ./calc_module/calc_module.c

parser.o:
	$(CC) $(CFLAGS) -c ./parse_module/parser.c

stack.o:
	$(CC) $(CFLAGS) -c ./data_structures/stack.c


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

