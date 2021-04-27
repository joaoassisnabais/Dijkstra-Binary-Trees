OBJS	= main.o fileData.o problems.o graphs.o binaryTree.o matrix.o
SOURCE	= main.c fileData.c problems.c graphs.c binaryTree.c matrix.c
HEADER	= fileData.h problems.h graphs.h binaryTree.h matrix.h
OUT	= aedmaps
CC	 = gcc
FLAGS	 = -g3 -c -Wall
LFLAGS	 = 

aedmaps: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c99

fileData.o: fileData.c
	$(CC) $(FLAGS) fileData.c -std=c99

problems.o: problems.c
	$(CC) $(FLAGS) problems.c -std=c99

graphs.o: graphs.c
	$(CC) $(FLAGS) graphs.c -std=c99

binaryTree.o: binaryTree.c
	$(CC) $(FLAGS) binaryTree.c -std=c99

matrix.o: matrix.c
	$(CC) $(FLAGS) matrix.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)

debug: $(OUT)
	valgrind $(OUT)

valgrind: $(OUT)
	valgrind $(OUT)

valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)