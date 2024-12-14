CC = gcc
CFLAGS = -Wall -Wpedantic -lcjson -ljson-c
FILES = config/ServerConfig.h src/main.c src/server/Server.* src/server/Handler.* src/server/http/* src/data/models/Book.* src/data/DataHandler.* src/helper/Utils.*

build:
	mkdir -p dist
	$(CC) $(FILES) $(CFLAGS) -o dist/webserver-tugas-besar