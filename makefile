JerryBoree:Jerry.o Hashtable.o LinkedList.o LinkedList.o JerryBoreeMain.o KeyValuePair.o MultiValueHashTable.o
	gcc Jerry.o Hashtable.o LinkedList.o JerryBoreeMain.o KeyValuePair.o MultiValueHashTable.o -o JerryBoree
Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c
Hashtable.o: Hashtable.c Hashtable.h Defs.h
	gcc -c Hashtable.c
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
JerryBoreeMain.o: JerryBoreeMain.c Defs.h
	gcc -c JerryBoreeMain.c
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c
MultiValueHashTable.o: MultiValueHashTable.c MultiValueHashTable.h Defs.h
	gcc -c MultiValueHashTable.c
clean:
	rm -f *.o JerryBoree