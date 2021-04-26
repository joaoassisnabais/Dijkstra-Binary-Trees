/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   matrix.c
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

void printMatrix(graph* g) {
    for(int i = 0; i < g->nv; i++) {
        for(int j = 0; j < g->nv; j++) {
            if(i != j)
                printf("%.2f  ",g->matrix[AccessM(i, j, g)]);
            else
                printf("0.00  ");
        }
        printf("\n");
    }
}

int AccessM(int va, int vb, graph* g){
    int result, min, max;

    if(va == vb) {
        return (g->nv*(g->nv-1)/2) + 1;
    }
    else if (va > vb){
        min=vb;
        max=va;
    }else{
        min=va;
        max=vb;
    }
    result= min + max*(max-1)/2;
    return result;
}

void createMandV(graph* g, int numV){
    g->matrix = (double*) malloc(sizeof(double)*((numV*(numV-1)/2) + 1));
    g->c = (char**) malloc(sizeof(char*) * numV);
    return;
}

void IniMatrix(double* matrix, int numV){
    int max = (numV*(numV-1)/2) + 1;
    for(int i=0; i<max; i++) matrix[i]=0;
}