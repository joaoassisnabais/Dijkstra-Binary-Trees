/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   graphs.c
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"

void createGraph(FILE* fp, graph* g){

    FILE* aux = fp;
    char* str[30]=NULL;
    int i=0, j=0;
    
    g->nv= (int*) malloc(sizeof(int));
    g->na= (int*) malloc(sizeof(int));
    fscanf(fp,"%d", g->nv);
    fscanf(fp,"%d", g->na);
    createMandV(g, g->nv);


    for (i=0; i<g->nv; i++){
        fscanf(fp,"%d", &j);
        fsacnf(fp, "%s", &str );
        strcpy(g->c[j], str);
    }

    for(i=0; i<g->na; i++){



    }

    return;

}
