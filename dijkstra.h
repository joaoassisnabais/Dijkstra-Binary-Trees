#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graphs.h"
#include "binaryTree.h"

typedef struct _QData QData;
typedef struct _PQueue PQueue;
struct _QData {
    int vert;       //vertex
    double cost;    //total cost
};

struct _PQueue {
    QData **data;
    int n_elements;
    int size;
};

bool compare(QData * item1, QData * item2);
PQueue * pqCreate(int size);
void pqAdd(PQueue * q, QData * item);
void pqModify(PQueue * q, int index, void * newpriority);
void pqMinDel(PQueue * h);
void pqErase(PQueue * q);
void * pqGetFirst(PQueue * q);
void heapSort(PQueue * h, int compare(const void *, const void *));

void pqPrint(PQueue * q, void printItem(const void *));


#endif /* Dijkstra_h */