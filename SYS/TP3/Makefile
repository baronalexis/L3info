# TP 4 Systeme de streaming audio

CC = gcc
CFLAGS = -Wall

all: bin/lecteur

bin/lecteur: ./bin ./obj obj/lecteur.o obj/audio.o 
	$(CC) $(CFLAGS) -o ./bin/lecteur ./obj/lecteur.o ./obj/audio.o -I./include


obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I./include

clean:
	rm *.o
