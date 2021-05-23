aedmaps: main.o fileData.o problems.o spt.o graphs.o binaryTree.o matrix.o
	gcc -Wall -std=c99 -O3 -o aedmaps main.o fileData.o problems.o spt.o graphs.o binaryTree.o matrix.o 
main.o: main.c fileData.h problems.h graphs.h binaryTree.h matrix.h
	gcc -Wall -std=c99 -O3 -c main.c
fileData.o: fileData.c fileData.h problems.h graphs.h binaryTree.h matrix.h
	gcc -Wall -std=c99 -O3 -c fileData.c
problems.o: problems.c problems.h graphs.h binaryTree.h matrix.h
	gcc -Wall -std=c99 -O3 -c problems.c
spt.o: spt.c spt.h graphs.h binaryTree.h matrix.h
	gcc -Wall -std=c99 -O3 -c spt.c
graphs.o: graphs.c graphs.h binaryTree.h matrix.h
	gcc -Wall -std=c99 -O3 -c graphs.c
binaryTree.o: binaryTree.c binaryTree.h matrix.h
	gcc -Wall -std=c99 -O3 -c binaryTree.c
matrix.o: matrix.c matrix.h
	gcc -Wall -std=c99 -O3 -c matrix.c
clean:
	rm -f *.o a.out aedmaps *~
