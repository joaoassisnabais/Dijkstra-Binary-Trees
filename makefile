aedmaps: main.o fileData.o graphs.o matrix.o
	gcc -Wall -std=c99 -g -o aedmaps main.o fileData.o graphs.o matrix.o
main.o: main.c fileData.h graphs.h matrix.h
	gcc -Wall -std=c99 -g -c main.c
fileData.o: fileData.c fileData.h graphs.h matrix.h
	gcc -Wall -std=c99 -g -c fileData.c
graphs.o: graphs.c graphs.h matrix.h
	gcc -Wall -std=c99 -g -c graphs.c
matrix.o: matrix.c matrix.h
	gcc -Wall -std=c99 -g -c matrix.c
clean:
	rm *.o
