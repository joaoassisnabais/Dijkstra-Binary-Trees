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

probs * extractProbs (char* opt, FILE* fp) {

    probs *input;
    char sigla[3];
    
    if (fgets(sigla, 2, fp) == NULL) exit(4);

    if (opt == "-1oo" || opt == "-1oa") {

    }
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
void openMapandOut(int i, char* input[], char* fileout, char* mapFile, FILE *fpMaps, FILE* fpout){

    char extout[] = ".queries";
    char *auxMap = NULL;

    mapFile = input[i]; 
    fileout = (char *) malloc((strlen(mapFile) + strlen(extout) - 4) * sizeof(char));
    auxMap = (char *) malloc((strlen(mapFile)- 4) * sizeof(char));
    for(int i=0; mapFile[i]=='.'; i++) auxMap[i]=mapFile[i]; 
    strcpy(fileout, auxMap);
    strcat(fileout, extout);

    fpMaps = fopen(mapFile, "r");
    if(fpMaps == NULL) {
        printf("ERROR cannot read map file %s\n", mapFile);
        return;
    }

    fpout = fopen(fileout, "w");
    if(fpout == NULL) {
        printf("ERROR cannot open exit file %s\n", fileout);
        return;
    }
    free(fileout);
    free(auxMap);
    return;
}

void selectProblems(FILE* fpProbs, FILE* fpout, graph* g, char* option, char* UI) {

    char *mode = NULL, *out=NULL;
    int v1=0,v2=0,k=0;

    while(fscanf(fpProbs,"%s", mode)){
        
        fscanf(fpProbs,"%d", &v1);
        if (strcmp(mode, "A0")==0) {
            A0 (g,v1);      //saída é um inteiro
        } else if (strcmp(mode, "B0")==0) {
            fscanf(fpProbs, "%d",&v2);
            B0(g, v1, v2);  //saída é um double com 2 casas decimais
        } else if (strcmp(mode, "C0")==0){
            C0(g,v1,k);
        } else if (strcmp(mode, "D0")==0){
            //D0();
        } else exit(3);

        if ((strcmp(option, "-1oo") == 0) || (strcmp(option, "-1oa") == 0)) break;
    }
    return;
}

void printexit(FILE* fpout, char* out, char* UI){



    return;
}