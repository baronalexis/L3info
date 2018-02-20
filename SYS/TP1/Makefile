# C Shell Makefile

CC = gcc
CFLAGS = -Wall


all: shell3


#Exerice 1
shell1: bin obj obj/shell1.o
	$(CC) $(CFLAGS) -o bin/shell1 obj/shell1.o

#Exercice 2
shell2: obj/shell2.o
	$(CC) $(CFLAGS) -o bin/shell2 obj/shell2.o

#Exercice 3
shell3: obj/shell3.o
	$(CC) $(CFLAGS) -o bin/shell3 obj/shell3.o

#Optionnel
shell3opt: obj/shell3opt.o
	$(CC) $(CFLAGS) -o bin/shell3opt obj/shell3opt.o
	

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm obj/*.o

mrproper: clean
	rm bin/*

bin:
	mkdir bin

obj:
	mkdir obj