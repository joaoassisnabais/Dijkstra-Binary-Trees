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
//#include "problems.h"

void extractProbs ( FILE* fp, char* option, char* prob ){

    FILE *aux = fp;
    char* buffer = NULL;

    while(fgets(buffer, 100, aux)!=NULL){

        strcat(prob, buffer);
        strcat(prob, "\n" );
        if ((strcmp(option, "-1oo") == 0) || (strcmp(option, "-1oa") == 0)) break;
    }
    return;
}
void openMapandOut(int i, char* argv[], char* fileout, char* mapFile, FILE *fpMaps){

    char extout[] = ".queries";
    char *auxMap = NULL;

    mapFile = argv[i]; 
    fileout = (char *) malloc((strlen(mapFile) + strlen(extout) - 4) * sizeof(char));
    auxMap = (char *) malloc((strlen(mapFile)- 4) * sizeof(char));
    for(int i=0; mapFile[i]=='.'; i++) auxMap[i]=mapFile[i]; 
    strcpy(fileout, auxMap);
    strcat(fileout, extout);

    fpMaps = fopen(mapFile, "r");
    if(fpMaps == NULL) {
        printf("ERROR cannot read map file %s\n", mapFile);
    }
    free(auxMap);
    return;
}

double selectProblems(graph* g, char* probs) {

    double sol=0;
    char *aux = NULL;
    sscanf(probs,"%s", aux);

    if (strcmp(aux, "A0")==0) {
        //A0();
    } else if (strcmp(aux, "B0")==0) {
        //B0();
    } else if (strcmp(aux, "C0")==0){
        //C0();
    } else if (strcmp(aux, "D0")==0){
        //D0();
    } else exit(3);

    return sol;
}


