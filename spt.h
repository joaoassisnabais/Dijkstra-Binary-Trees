#ifndef SPT_H
#define SPT_H

#include <stdbool.h>
#include "graphs.h"
#include "binaryTree.h"

typedef struct _QData QData;
typedef struct _PQueue PQueue;

struct _QData {
    bool visited;
    int index;
    int previous;
    double cost;    //total cost
};

struct _PQueue{
    QData *data;
    int *qVertex;
    int n_elements;
    int size;
};

void pqTree(node* tree, PQueue** q, double currentCost, int previous);
int * dijkstra(data *g, int src, int end);

#endif /* Spt_h */