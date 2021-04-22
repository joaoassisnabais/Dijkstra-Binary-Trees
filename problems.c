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

    int sol=0, degree=0;
    int max=g->nv*(g->nv-1)/2;

    if((vertex<=g->nv) & (vertex>0)){
        for (int i=0; i<max; i++){
            if(i!=vertex)
                if (g->matrix[AccessM(vertex, i)] != 0) degree++;
        }
    }
    else return -1;

    return degree;
}