/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
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

#define MAPS 4

probs * extractProbs (char* opt, FILE* fp) {

    probs *output = NULL, *linha = NULL;
    int i = 0, vertAux;
    char probAux[3];

    while(fscanf(fp, "%s %d", probAux, &vertAux) != EOF) {    //Ler problema e primeiro vértice
        if(i == 0) {
            output = (probs*) malloc(sizeof(probs));
            output->next = NULL;
            linha = output;
        } else {
            linha->next = (probs*) malloc(sizeof(probs));
            linha = linha->next;
            linha->next = NULL;
        }
        strcpy(linha->problema, probAux);
        linha->vertice = vertAux;
        if(strcmp(linha->problema, "A0") != 0) {
            if(fscanf(fp, "%d", &linha->verticeOrK) == 0) exit(4);
        }
        i++;
        if(strcmp(opt, "-1oo") == 0 || strcmp(opt, "-1oa") == 0) break;
    }
    if(i == 0) exit(4);

    return output;
}

/*
void extractProbs ( FILE* fp, char* option, char* prob ){

    FILE *aux = fp;
    char buffer[100];

    while(fgets(buffer, 100, aux)!=NULL){

        strcat(prob, buffer);
        strcat(prob, "\n" );
        if ((strcmp(option, "-1oo") == 0) || (strcmp(option, "-1oa") == 0)) break;
    }
    return;
}
*/
void openMapandOut(int i, char* input[], char* mapFile, FILE** fpMaps, FILE** fpout) {

    char extout[] = "queries";
    char *fileout = NULL;

    mapFile = input[i]; 
    fileout = (char *) malloc((strlen(mapFile) + strlen(extout) - MAPS + 1));
    strncpy(fileout, mapFile, strlen(mapFile) - 4);
    strcat(fileout, extout);
    fileout[strlen(fileout) - 1] = '\0';

    *fpMaps = fopen(mapFile, "r");
    if(fpMaps == NULL) {
        printf("ERROR cannot read map file %s\n", mapFile);
        return;
    }

    *fpout = fopen(fileout, "w");
    if(fpout == NULL) {
        printf("ERROR cannot open exit file %s\n", fileout);
        return;
    }
    free(fileout);
    return;
}

void selectProblems(probs* headProbs, FILE* fpout, graph* g, char* UI) {

    int solInt = 0;
    double solDbl = 0;
    probs *auxProbs = headProbs;

    fprintf(fpout, "%s\n\n", UI);

    while(auxProbs != NULL){
        
        if (strcmp(auxProbs->problema, "A0")==0) {
            solInt = A0(g,auxProbs->vertice);      //saída é um inteiro
            fprintf(fpout, "%d %d %s %d %d\n\n", g->nv, g->na, auxProbs->problema, auxProbs->vertice, solInt);
        } else if (strcmp(auxProbs->problema, "B0")==0) {;
            solDbl = B0(g, auxProbs->vertice, auxProbs->verticeOrK);  //saída é um double com 2 casas decimais
            fprintf(fpout, "%d %d %s %d %d %f\n\n", g->nv, g->na, auxProbs->problema, auxProbs->vertice, auxProbs->verticeOrK,solDbl);
        } else if (strcmp(auxProbs->problema, "C0")==0){
            solInt = C0(g,auxProbs->vertice,auxProbs->verticeOrK);
            fprintf(fpout, "%d %d %s %d %d %d\n\n", g->nv, g->na, auxProbs->problema, auxProbs->vertice, auxProbs->verticeOrK,solInt);
        } else if (strcmp(auxProbs->problema, "D0")==0){
            //solInt = D0();
            fprintf(fpout, "%d %d %s %d %d %d\n\n", g->nv, g->na, auxProbs->problema, auxProbs->vertice, auxProbs->verticeOrK,solInt);
        } else exit(3);

        auxProbs = auxProbs->next;
    }
    return;
}