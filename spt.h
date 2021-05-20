#ifndef SPT_H
#define SPT_H

#include <stdbool.h>
#include "graphs.h"
#include "binaryTree.h"

typedef struct _QData QData;
typedef struct _PQueue PQueue;
typedef struct _Parent parentArray;

struct _QData {
    bool visited;
    int index;
    int previous;
    double cost;    //total cost
    double parentCost;
};

struct _PQueue{
    QData *data;
    int *qVertex;
    int n_elements;
    int size;
};

struct _Parent{
    int vertex;
    double cost;
};

parentArray * dijkstra(data *g, int src, int end, double* totalCost, int va, int vb);

#endif /* Spt_h */