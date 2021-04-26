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
struct _bfsmatrix  {
    int maxSteps;
    int verticesAtK;
};

int A0 (graph *g, int vertex);
double B0 (graph *g, int v1, int v2);
int C0 (graph *g, int v1, int k);
int D0 (graph *g, int v1, int k);
bfsOut* bfsMatrix(graph *g, int v, int k);
#endif