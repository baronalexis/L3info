
CFLAGS = -Wall -g
CC = gcc
EXEC = bin/word_search_engine

all:
	$(EXEC)


bin/word_search_engine: obj/file.o obj/hash.o obj/main.o
	$(CC) -o ./bin/word_search_engine obj/file.o obj/hash.o obj/main.o -I ./include $(CFLAG)


obj/file.o: src/file.c
	$(CC) -c -o obj/file.o src/file.c -I ./include


obj/hash.o: src/hash.c
	$(CC) -c -o obj/hash.o src/hash.c -I ./include


obj/main.o: src/main.c
	$(CC) -c -o obj/main.o src/main.c -I ./include


listing:
	a2ps -o listing.ps include/functions.h include/types.h src/file.c src/hash.c src/main.c
	ps2pdf listing.ps
	rm listing.ps

clean :
	rm -rf obj/*.o bin/word_search_engine
