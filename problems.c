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

int A0 (graph *g, int vertex){

    int degree=0;

    if((vertex <= g->nv) && (vertex > 0)){
        for (int i = 0; i < g->nv; i++){
            if(i != ACS(vertex)){
                if (g->matrix[AccessM(ACS(vertex), i, g)] != 0)
                    degree++;
            }
        }
    }
    else return -1;

    return degree;
}
double B0 (graph *g, int v1, int v2){

    double sol=0;

    if( ((v1<=g->nv) && (v1>0)) && ((v2<=g->nv) && (v2>0)) ){
        if(v1!=v2)
            sol=g->matrix[AccessM(ACS(v1),ACS(v2), g)];
    }
    if(sol==0) return -1;

    return sol;
}

int C0 (graph *g, int v1, int k){

    int sol=0,steps=0;

    if((v1<=g->nv) && (v1>0)){  //verificação da existência do vértice
        steps=bfsMatrix(g,ACS(v1), k);
        if(k <= steps && k >= 0) sol=1;
        else sol=0;
    }else sol=-1;

    return sol;
}

int bfsMatrix(graph *g, int v, int k) {
    
    queue *q = NULL;
    int *visited = (int *) calloc(g->nv,sizeof(int));
    //int *added = (int *) calloc(g->nv,sizeof(int));
    int maxSteps=0;
    
    q = qAdd(q,v);
    while (q->top != NULL){
        if (visited[q->top->v] == 0){//verificação de vértice visitado
            visited[q->top->v] = 1;
            if(q->top->steps > maxSteps){//ADICIONAR VERIFICAÇÃO COM K
                maxSteps = q->top->steps;
                if(maxSteps == k)
                    break;
            }
            for (int i=0; i<g->nv; i++){
                if ((g->matrix[AccessM(q->top->v,i,g)] != 0) && (visited[i]==0)){
                        q = qAdd(q,i);
                }
            }
        }
        qPop(q);
    }
    //free(added);
    free(visited);
    qFree(q);
    return maxSteps;
}

