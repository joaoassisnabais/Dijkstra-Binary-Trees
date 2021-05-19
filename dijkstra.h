#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdbool.h>
#include "graphs.h"
#include "binaryTree.h"

typedef struct _QData QData;
typedef struct _PQueue PQueue;
struct _QData {
    bool visited;
    int index;
    double cost;    //total cost
};

struct _PQueue{
    QData *data;
    int *qVertex;
    int n_elements;
    int size;
};

bool compare(QData item1, QData item2);
PQueue * pqCreate(int size);
void pqAdd(PQueue * q, QData item);
void pqModify(PQueue * q, int index, int newcost);
void pqMinDel(PQueue * h);
void pqErase(PQueue * q);
QData pqGetFirst(PQueue * q);
void heapSort(PQueue * h, int compare(const void *, const void *));

void pqPrint(PQueue * q, void printItem(const void *));


#endif /* Dijkstra_h */