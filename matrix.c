/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   matrix.c
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"

int AccessMatrix(int va, int vb){
    int result, min, max;

    if (va > vb){
        min=vb;
        max=va;
    }else{
        min=va;
        max=vb;
    }

    result=
}

void createMandV(graph* g, int numV){
    g->matrix = (double*) malloc(sizeof(double)*(numV*(numV - 1)/2));
    g->c = (char*) malloc(sizeof(char)*numV*26);

    return;
}