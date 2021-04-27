aedmaps: main.o fileData.o problems.o graphs.o binaryTree.o matrix.o
	gcc -Wall -std=c99 -g -o aedmaps main.o fileData.o problems.o graphs.o binaryTree.o matrix.o 
main.o: main.c fileData.h problems.h graphs.h binaryTree.h matrix.h
	gcc -Wall -std=c99 -g -c main.c
fileData.o: fileData.c fileData.h problems.h graphs.h binaryTree.h matrix.h
	gcc -Wall -std=c99 -g -c fileData.c
problems.o: problems.c problems.h graphs.h binaryTree.h matrix.h
	gcc -Wall -std=c99 -g -c problems.c
graphs.o: graphs.c graphs.h binaryTree.h matrix.h
	gcc -Wall -std=c99 -g -c graphs.c
binaryTree.o: binaryTree.c binaryTree.h matrix.h
	gcc -Wall -std=c99 -g -c binaryTree.c
matrix.o: matrix.c matrix.h
	gcc -Wall -std=c99 -g -c matrix.c
clean:
	rm *.o