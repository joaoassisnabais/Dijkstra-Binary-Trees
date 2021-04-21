aedmaps: main.o fileData.o graphs.o
	gcc -Wall -std=c99 -g -o aedmaps main.o fileData.o graphs.o 
main.o: main.c fileData.h graphs.h
	gcc -Wall -std=c99 -g -c main.c
fileData.o: fileData.c fileData.h graphs.h
	gcc -Wall -std=c99 -g -c fileData.c
graphs.o: graphs.c graphs.h
	gcc -Wall -std=c99 -g -c graphs.c
clean:
	rm *.o
