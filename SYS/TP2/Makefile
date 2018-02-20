# TP 3 Mémoire partagée Makefile

CC = gcc
CFLAGS = -Wall

all: tp3

#Exerice 1
tp3: tp3.o
	$(CC) $(CFLAGS) -o tp3 tp3.o

nettoie: nettoie.o
	$(CC) $(CFLAGS) -o nettoie nettoie.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o
