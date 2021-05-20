/******************************************************************************
 * (c) 2021 - João Nabais & João Coelho
 *
 * NAME
 *   fileData.c
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

#define MAPS 4

probs * extractProbs (char* opt, FILE* fp) {

    probs *output = NULL, *linha = NULL;
    int i = 0, vaux1, vaux2;
    char probAux[3];

    while(fscanf(fp, "%s %d %d", probAux, &vaux1, &vaux2) != EOF) {    //Ler problema e primeiro vértice
        if(i==0) {
            output = (probs*) malloc(sizeof(probs));
            if(output==NULL) exit(0);
            output->next = NULL;
            linha = output;
            i++;
        } else {
            linha->next = (probs*) malloc(sizeof(probs));
            if(linha==NULL) exit(0);
            linha = linha->next;
            linha->next = NULL;
        }
        strcpy(linha->problema, probAux);
        linha->va=vaux1;
        linha->vb=vaux2;
        if( (strcmp(linha->problema, "C1") == 0) || (strcmp(linha->problema, "D1") == 0) ){
            if(fscanf(fp, "%d", &linha->k) == 0) exit(0);
        }
        if( (strcmp(linha->problema, "B1") == 0) ){
            if(fscanf(fp, "%c %lf", &linha->id, &linha->cost) == 0) exit(0);
        }
        if(strcmp(opt, "-oo") == 0 || strcmp(opt, "-oa") == 0) break;
    }
    if(i == 0) exit(0);

    return output;
}

void openMapandOut(char* mapFile, FILE** fpMaps, FILE** fpout) {

    char extout[] = "queries";
    char *fileout = NULL;

    fileout = (char *) malloc((strlen(mapFile) + strlen(extout) - MAPS + 1));
    if(fileout==NULL) exit(0);

    snprintf(fileout, strlen(mapFile)- MAPS + 1, "%s", mapFile);
    strcat(fileout, extout);

    *fpMaps = fopen(mapFile, "r");
    if(fpMaps == NULL) exit(0);

    *fpout = fopen(fileout, "w");
    if(fpout == NULL) exit(0);

    free(fileout);
    return;
}

void selectProblems(probs* headProbs, FILE* fpout, data* g) {

    probs *auxProbs = headProbs;

    while(auxProbs != NULL){
        
        if (strcmp(auxProbs->problema, "A1")==0) {

            A1(fpout, g,auxProbs->va, auxProbs->vb);

        } else if (strcmp(auxProbs->problema, "B1")==0) {

            B1(g, auxProbs->va, auxProbs->vb, auxProbs->id, auxProbs->cost);

        } else if (strcmp(auxProbs->problema, "C1")==0){

            C1(g,auxProbs->va, auxProbs->vb, auxProbs->k);

        } else if (strcmp(auxProbs->problema, "D1")==0){

            D1(g,auxProbs->va, auxProbs->vb, auxProbs->k);

        } else exit(0);

        auxProbs = auxProbs->next;
    }
    return;
}

void freeProbs(probs *p){

    probs *aux = p;

    while(p != NULL){
        p = aux->next;
        free(aux);
        aux = p;
    }
}