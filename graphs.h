/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   graphs.h
 *
 ******************************************************************************/

#ifndef GRAPHS_H
#define GRAPHS_H

typedef struct _Graph graph;
typedef struct _QueueNode qnode;
typedef struct _Queue queue;
#include "binaryTree.h"
struct _Graph
{
    double *matrix;     //matriz reduzida que na verdade é um vetor
    char **c;           //string dos id's da localização (26 pq é o número max de caracteres possiveis)
    int nv;             //número de vértices
    int na;             //número de arestas
};

struct _QueueNode{
    int v;
    int steps;
    struct _QueueNode * next;
};

struct _Queue {
    qnode * top;
    qnode * bottom;
};

void createGraphM(FILE** fp, graph* g);
void freeGraphM(graph* g);
void CreateGraphBT(FILE **fp, data *g);
queue * qAdd(queue *q, int i);
void qPop(queue * q);
int qExist(queue * q);
void qFree(queue * q);
void qPrint(queue * q);

#endif
