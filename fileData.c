/******************************************************************************
 * (c) 2021 João Nabais & João Nabais
 *
 * NAME
 *   fileData.c
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"

void extractProbs ( FILE* fp, char* option, char* prob ){

    FILE *aux = fp;
    char* buffer;

    while(fgets(buffer, 100, aux)!=NULL){

        strcat(prob, buffer);
        strcat(prob, "\n" );
        if ((strcmp(option, "-1oo") == 0) || (strcmp(option, "-1oa") == 0)) break;
    }
    return;
}
void iniMap(int i, char* argv[], char* fileout, char* mapFile, FILE *fpMaps){

    char extout[] = ".queries";

    mapFile = argv[i]; 
    fileout = (char *) malloc((strlen(mapFile) + strlen(extout) +1) * sizeof(char));
    strcpy(fileout, mapFile);
    strcat(fileout, extout);

    fpMaps = fopen(mapFile, "r");
    if(fpMaps == NULL) {
        printf("ERROR cannot read map file %s\n", mapFile);
    }

    return;
}
