/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   graphs.h
 *
 ******************************************************************************/

#ifndef GRAPHS_H
#define GRAPHS_H

typedef struct _Graph
{
    double *matrix;     //matriz reduzida que na verdade é um vetor
    char **c;           //string dos id's da localização (26 pq é o número max de caracteres possiveis)
    int nv;             //número de vértices
    int na;             //número de arestas

}graph;

void createGraph(FILE* fp, graph* g);

#endif
