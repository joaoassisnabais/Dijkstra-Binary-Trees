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

    printf("\n");
    printMatrix(g);

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

    if( ((v1<=g->nv) && (v1>0)) || ((v2<=g->nv) && (v2>0)) ){
        if(v1!=v2)
            sol=g->matrix[AccessM(ACS(v1),ACS(v2), g)];
    }
    if(sol==0) return -1;

    return sol;
}

int C0 (graph *g, int v1, int k){

    int *visited = (int*) malloc(sizeof(int)*g->nv);

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
	int i;

    printf("\n\n");
    printMatrix(g);
    printf("\n%f\n", g->matrix[AccessM(7,7, g)]);

	visited[v]=1;
	for (i = 0;i < g->nv;i++){
        if(steps == k)break;
        if(g->matrix[AccessM(v,i,g)] != 0 && !visited[i]) {
            steps++;
            if(steps == k)break;
            steps=dfsDegree(g,i, visited, steps, k);
            if(steps == k)break;
            steps--;
        }
	}
    return steps;
}