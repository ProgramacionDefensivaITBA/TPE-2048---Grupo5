all:
	gcc -o -Wall -pedantic frontend.c backend.c backend.h getnum2.c getnum.h
