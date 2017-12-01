
CFLAGS = -Wall -g
CC = gcc
EXEC = bin/word_search_engine

all: $(EXEC) test

test:
	chmod u+x ./bin/word_search_engine
	./bin/word_search_engine


bin/word_search_engine: ./bin ./obj  obj/hash.o obj/file.o obj/main.o
	$(CC) -o ./bin/word_search_engine ./obj/hash.o ./obj/file.o ./obj/main.o $(CFLAGS)

obj/hash.o: src/hash.c include/functions.h
	$(CC) -o ./obj/hash.o -c ./src/hash.c -I./include $(CFLAGS)

obj/main.o: src/main.c include/types.h include/functions.h
	$(CC) -o ./obj/main.o -c ./src/main.c -I./include $(CFLAGS)

obj/file.o: src/file.c include/types.h include/functions.h
	$(CC) -o ./obj/file.o -c ./src/file.c -I./include $(CFLAGS)

listing:
	a2ps -o listing.ps ./include/functions.h include/types.h ./src/file.c ./src/hash.c ./src/main.c
	ps2pdf listing.ps
	rm listing.ps

clean:
	rm -rf ./obj/*.o ./bin/word_search_engine

./obj:
	mkdir obj

./bin:
	mkdir bin
