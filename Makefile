all:
	gcc -Wall -pedantic -o 2048 frontend.c backend.c backend.h getnum2.c getnum.h
