/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   problems.h
 *
 ******************************************************************************/

#ifndef PROBLEMS_H
#define PROBLEMS_H

typedef struct _bfsmatrix bfsOut;
#include "binaryTree.h"
struct _bfsmatrix  {
    int maxSteps;
    int verticesAtK;
};

int A0 (data *g, int vertex);
double B0 (data *g, int v1, int v2);
int C0 (data *g, int v1, int k);
int D0 (data *g, int v1, int k);
bfsOut* bfsMatrix(graph *g, int v, int k);
bfsOut* bfsBT (data *g, int v, int k);
#endif