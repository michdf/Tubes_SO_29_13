CC = gcc
CFLAGS = -Wall -Wpedantic -Werror

build:
	cc src/server/Server.c src/server/Server.h src/server/test.c -o dist/webserver-tugas-besar