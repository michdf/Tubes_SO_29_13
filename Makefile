CC = gcc
CFLAGS = -Wall -Wpedantic -lcjson -ljson-c
FILES = src/main.c src/server/Server.* src/server/Handler.* src/server/http/* src/data/models/book.* src/data/data_handler.* src/helper/Utils.*

build:
	mkdir -p dist
	$(CC) $(FILES) $(CFLAGS) -o dist/webserver-tugas-besar