CFLAGS = -Wall -g


bin/test_list: obj/list.o obj/test_list.o
	gcc -o ./bin/test_list obj/list.o obj/test_list.o -I ./include $(CFLAG)


obj/list.o: src/list.c
	gcc -c -o obj/list.o src/list.c -I ./include



obj/test_list.o: src/test_list.c
	gcc -c -o obj/test_list.o src/test_list.c -I ./include


listing:
	a2ps -o listing.ps include/list.h src/list.c src/test_list.c
	ps2pdf listing.ps
	rm listing.ps

clean :
	rm -rf obj/*.o bin/test_list

test_list :
	make
	./bin/test_list < commands.txt
