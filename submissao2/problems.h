/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   problems.h
 *
 ******************************************************************************/

#ifndef PROBLEMS_H
#define PROBLEMS_H
#include "binaryTree.h"

typedef struct _bfsmatrix bfsOut;
struct _bfsmatrix  {
    int maxSteps;
    int verticesAtK;
};

int A0 (data *g, int vertex);
double B0 (data *g, int v1, int v2);
int C0 (data *g, int v1, int k);
int D0 (data *g, int v1, int k);
bfsOut* bfsTree(data *g, int v, int k);
void A1(FILE* fp, data* g, int va, int vb);
void B1(FILE* fp, data* g, int va, int vb, char id, double cost);
void C1(FILE* fp, data* g, int va, int vb, int k);
void D1(FILE* fp, data* g, int va, int vb, int k);
#endif