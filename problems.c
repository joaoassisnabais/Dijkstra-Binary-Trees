/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   problems.c
 *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"
#include "problems.h"
#include "binaryTree.h"

int A0 (data *g, int vertex){

/*    int degree=0;

    if((vertex <= g->nv) && (vertex > 0)){
        for (int i = 0; i < g->nv; i++){
            if(i != ACS(vertex)){
                if (g->matrix[AccessM(ACS(vertex), i, g)] != 0)
                    degree++;
            }
        }
    }
    else return -1;
*/
    return g->table[ACS(vertex)].n_links;
}

double B0 (data *g, int v1, int v2){

    /*double sol=0;
    if( ((v1<=g->nv) && (v1>0)) && ((v2<=g->nv) && (v2>0)) ){
        if(v1!=v2)
            sol=g->matrix[AccessM(ACS(v1),ACS(v2), g)];
    }
    if(sol==0) return -1;

    return sol;*/
    node* aux=NULL;
    aux = FindNode(g->table[ACS(v1)].root, v2);
    return aux->cost;

}

int C0 (data *g, int v1, int k){

    int sol=0,steps=0;
    bfsOut* outputBfs;

    if((v1<=g->nv) && (v1>0)){  //verificação da existência do vértice
        outputBfs = bfsBT(g,ACS(v1), k);
        steps=outputBfs->maxSteps;
        free(outputBfs);
        if(k <= steps && k >= 0) sol=1;
        else sol=0;
    }else sol=-1;

    return sol;

}

int D0 (data *g, int v1, int k){

    int sol=0;
    bfsOut* outputBfs;

    if((v1<=g->nv) && (v1>0)){  //verificação da existência do vértice
        outputBfs=bfsBT(g,ACS(v1), k+1);
        sol = outputBfs->verticesAtK;
        free(outputBfs);
    }else sol = -1;

    return sol;
}

bfsOut* bfsMatrix(graph *g, int v, int k) {
    
    queue *q = NULL;
    int *visited = (int *) calloc(g->nv,sizeof(int));
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
            if(q->top->steps == k-1) 
                output->verticesAtK++;

            for (int i=0; i<g->nv; i++){
                if ((g->matrix[AccessM(q->top->v,i,g)] != 0) && (visited[i]==0)){
                    q = qAdd(q,i);
                }
            }
        }
        qPop(q);
    }
    free(visited);
    qFree(q);
    return output;
}

bfsOut* bfsBT (data *g, int v, int k){

    queue *q = NULL;
    int *visited = (int *) calloc(g->nv,sizeof(int));
    bfsOut* output = (bfsOut*) malloc(sizeof(bfsOut));
    int *qNext=NULL, auxIndex=0;
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
            if(q->top->steps == k-1) 
                output->verticesAtK++;

            qNext=(int *)calloc(g->table[q->top->v].n_links,sizeof(int));
            SeeTree(g->table[q->top->v].root, qNext, &auxIndex);
            for(int i=0; i<g->table[q->top->v].n_links; i++){
                if(visited[ACS(qNext[i])]==0) 
                    qAdd(q,ACS(qNext[i]));
            }
            free(qNext);
            auxIndex=0;

        }
        qPop(q);
    }
    free(visited);
    qFree(q);
    return output;
}
