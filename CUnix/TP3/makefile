#
# Link
#

CFLAGS = -Wall -g


bin/test_list: obj/list.o obj/test_list.o
# To be completed
	gcc -o ./bin/test_list obj/list.o obj/test_list.o -I ./include $(CFLAG)


#
# Objets of TP Lists
#

obj/list.o: src/list.c
# To be completed
	gcc -c -o obj/list.o src/list.c -I ./include





obj/test_list.o: src/test_list.c
# To be completed
	gcc -c -o obj/test_list.o src/test_list.c -I ./include




#
# Listing creation in pdf
#

listing:
	a2ps -o listing.ps include/list.h src/list.c src/test_list.c
	ps2pdf listing.ps
	rm listing.ps

#
# Remove files
#

clean :
# To be completed
	rm -rf obj/*.o bin/test_list
#
# Test the functionality 
#

test : bin/test_list
# To be completed
