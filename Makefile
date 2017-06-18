.PHONY: all clean makedir test
COMPILE = g++
DEF_FLAGS_COMPILE = -std=c++11





all: main

clean:
	rm -rf build/src/*
	rm -rf build/test/*

makedir:
	mkdir bin
	mkdir build
	mkdir build/src
	mkdir build/test

deletedir:
	rm -rf build/test
	rm -rf build/src
	rm -rf build
	rm -rf bin



#сборка приложения
main: src/main.cpp
	$(COMPILE) $(DEF_FLAGS_COMPILE) -o bin/a.exe src/main.cpp
# build/src/main.o: src/main.cpp
# 	$(COMPILE) $(DEF_FLAGS_COMPILE) -c -o build/src/main.o src/main.cpp

# main: deletedir makedir build/src/main.o
# 	$(COMPILE) $(DEF_FLAGS_COMPILE) -o bin/a.exe build/src/main.o



#сборка теста
# build/test/main.o: test/main.c
# 	gcc -Wall -Werror -c -o build/test/main.o test/main.c

# build/test/validation_test.o: test/validation_test.c
# 	gcc -Wall -Werror -c -o build/test/validation_test.o test/validation_test.c

# build/test/deposit_test.o: test/deposit_test.c
# 	gcc -Wall -Werror -c -o build/test/deposit_test.o test/deposit_test.c

# test: deletedir makedir build/test/main.o build/test/validation_test.o build/test/deposit_test.o build/src/depcalc.o
# 	gcc -Wall -Werror -o bin/test build/test/main.o build/test/validation_test.o build/test/deposit_test.o build/src/depcalc.o
