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
    int max=g->nv*(g->nv-1)/2;

    printMatrix(g->matrix, g->nv);

    if((vertex<=g->nv) && (vertex>0)){
        for (int i=0; i<max; i++){
            if(i!= ACS(vertex)){
                if (g->matrix[AccessM(ACS(vertex), i)] != 0)
                    degree++;
            }
        }
    }
    else return -1;

    return degree;
}
double B0 (graph *g, int v1, int v2){

    double sol=0;

    if( ((v1<=g->nv) && (v1>0)) || ((v2<=g->nv) && (v2>0)) ){
        if(v1!=v2)
            sol=g->matrix[AccessM(ACS(v1),ACS(v2))];
    }
    if(sol==0) return -1;

    return sol;
}

int C0 (graph *g, int v1, int k){

    int max=g->nv*(g->nv-1)/2;
    int *visited = (int*) malloc(sizeof(int)*max);

    if((v1<=g->nv) && (v1>0)){
        if(k==dfsDegree(g,ACS(v1), visited, 0, k)){
            free(visited);   
            return 1;
        }else{
            free(visited);
            return 0;
        }
    }
    free(visited);
    return -1;
}

int dfsDegree(graph* g,int v, int *visited, int steps, int k) {
	int i, max=g->nv*(g->nv-1)/2;
	visited[v]=1;
	for (i=1;i<=max;i++){
        if(g->matrix[AccessM(v,i)]!=0 && !visited[i]) {
            steps++;
            steps=dfsDegree(g,i, visited, steps, k);
            if(steps == k)break;
            steps--;
        }
	}
    return steps;
}