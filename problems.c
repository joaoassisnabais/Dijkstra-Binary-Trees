/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   problems.c
 *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"
#include "problems.h"
#include "binaryTree.h"

int A0 (data *g, int vertex) {

    if((vertex <= g->nv) && (vertex > 0))
        return g->table[ACS(vertex)].nLinks;
    else return -1;
}

double B0 (data *g, int v1, int v2) {

    node* link;

    if(((v1 <= g->nv) && (v1 > 0)) && ((v2 <= g->nv) && (v2 > 0))) {
        if(v1==v2)
            return -1;
        else if(g->table[ACS(v1)].nLinks < g->table[ACS(v2)].nLinks)    //check which one has the least link, to make the search faster
            link = FindNode(g->table[ACS(v1)].root, v2);
        else
            link = FindNode(g->table[ACS(v2)].root, v1);
    } else
        return -1;

    if(link == NULL)
        return -1;
    else
        return link->cost;
}

int C0 (data *g, int v1, int k){

    int steps=0;
    bfsOut* outputBfs;

    if((v1<=g->nv) && (v1>0)){  //verificação da existência do vértice
        if(k == 0)
            return 1;
        if(k < 0)
            return 0;
        outputBfs = bfsTree(g,ACS(v1), k);
        steps=outputBfs->maxSteps;
        free(outputBfs);
        if(k <= steps)
            return 1;
        else
            return 0;
    }else
        return -1;
}

int D0 (data *g, int v1, int k){

    int sol=0;
    bfsOut* outputBfs;

    if((v1<=g->nv) && (v1>0)){  //verificação da existência do vértice
        outputBfs=bfsTree(g,ACS(v1), k+1);
        sol = outputBfs->verticesAtK;
        free(outputBfs);
    }else sol = -1;

    return sol;
}

bfsOut* bfsTree(data *g, int v, int k) {
    
    queue *q = NULL;
    int *visited = (int *) calloc(g->nv,sizeof(int));
    //int *added = (int *) calloc(g->nv,sizeof(int));
    bfsOut* output = (bfsOut*) malloc(sizeof(bfsOut));
    output->maxSteps = 0;
    output->verticesAtK = 0;
    
    q = qAdd(q,v);
    while (q->top != NULL){
        if (visited[q->top->v] == 0){//verificação de vértice visitado
            visited[q->top->v] = 1;
            if(q->top->steps > output->maxSteps) { //ADICIONAR VERIFICAÇÃO COM K
                output->maxSteps = q->top->steps;
                if(output->maxSteps == k)
                    break;
            }
            if(q->top->steps == k-1)    //usado para D0, com k+1 de input
                output->verticesAtK++;

            qTree(g->table[q->top->v].root, &q, visited);
        }
        qPop(q);
    }
    //free(added);
    free(visited);
    qFree(q);
    return output;
}

