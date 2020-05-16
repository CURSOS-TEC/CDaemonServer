CC = gcc
main: daemon.c
	@${CC} daemon.c -o daemon.o