/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   graphs.c
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"
#include "problems.h"

void createGraph(FILE* fp, graph* g){

    char str[30];
    int i=0, j=0, va, vb, l;
    double cost;
    
    fscanf(fp,"%d", &g->nv);
    fscanf(fp,"%d", &g->na);
    createMandV(g, g->nv);

    //colocar os valores dos ids na matriz
    for (i=0; i<g->nv; i++){
        fscanf(fp,"%d", &j);
        fscanf(fp, "%s", str );
        l = strlen(str) + 1;
        g->c[j] = (char*) malloc(l);
        strcpy(g->c[j], str);//fazer define -1
        g->c[j][l-1] = '\0';
    }
    IniMatrix(g->matrix, g->nv);
    
    //colocar os custos na matriz de adjacência
    for(i=0; i<g->na; i++){
        fscanf(fp,"%d", &va);
        fscanf(fp,"%d", &vb);
        fscanf(fp,"%lf", &cost);
        g->matrix[AccessM(va,vb)] = cost;
    }
    return;
}
