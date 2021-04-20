/******************************************************************************
 * (c) 2021 João Nabais & João Nabais
 *
 * NAME
 *   graphs.h
 *
 ******************************************************************************/

#ifndef GRAPHS_H
#define GRAPHS_H

typedef struct _Id
{
    char Id[26];    //string dos id's da localização
}Id;

typedef struct _Graph
{
    double *matrix;     //matriz reduzida que na verdade é um vetor
    Id *c;              //string dos id's da localização
    int nv;             //número de vértices
    int na;             //número de arestas

}graph;



#endif
