CC = gcc
CFLAGS = -Wall -Wpedantic -Werror

FILES = src/main.c src/server/Server.* src/server/Handler.* src/server/http/*

build:
	mkdir -p dist
	cc $(FILES) -o dist/webserver-tugas-besar