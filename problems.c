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

    if((vertex<=g->nv) && (vertex>0)){
        for (int i=0; i<max; i++){
            if(i!=vertex){
                if (g->matrix[AccessM(vertex, i)] != 0) degree++;
            }
        }
    }
    else return -1;

    return degree;
}
double B0 (graph *g, int v1, int v2){

    double sol=0;

    if( ((v1<=g->nv) && (v1>0)) || ((v2<=g->nv) && (v2>0)) ){
        if(v1!=v2) sol=g->matrix[AccessM(v1,v2)];
    }
    if(sol==0) return -1;

    return sol;
}

int C0 (graph *g, int v1, int k){

    int max=g->nv*(g->nv-1)/2;
    int *reach = (int*) malloc(sizeof(int)*max);

    if((v1<=g->nv) && (v1>0)){
        if(k==dfs(g,v1, reach, 0, k)) return 1;
        else return 0;
    }

    return -1;
}

int dfs(graph* g,int v, int *reach, int steps, int k) {
	int i, max=g->nv*(g->nv-1)/2;
	reach[v]=1;
	for (i=1;i<=max;i++){
        if(g->matrix[AccessM(v,i)]!=0 && !reach[i]) {
            steps++;
            steps=dfs(g,i, reach, steps, k);
            if(steps == k)break;
            steps--;
        }
	}
    return steps;
}