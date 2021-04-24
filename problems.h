/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   problems.h
 *
 ******************************************************************************/

#ifndef PROBLEMS_H
#define PROBLEMS_H

int A0 (graph *g, int vertex);
double B0 (graph *g, int v1, int v2);
int C0 (graph *g, int v1, int k);
int dfsDegree(graph* g,int v, int *degree, int steps, int k);
void bfsDegree(graph* g, int v, int *visited, int *queue, int *level, int qindex, int order);
#endif