/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   main.c
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"
#include "problems.h"

int main (int argc, char *argv[]){

    FILE *fpProbs, *fpMaps = NULL, *fpProbsAux, *fpOut = NULL;
    char *opt, *probFile, *mapFile = NULL, *fileout = NULL, *prob = NULL, *userInput = NULL;
    int UIsz=0;
    graph *g;
    g = (graph*) malloc(sizeof(graph));

    if(argc<4){
        printf("Not enough arguments \n");
        exit(1);
    }

    //extracting cmd line arguments without any map     
    opt = argv[1];
    probFile = argv[2];

    fpProbs = fopen(probFile, "r");
    if(fpProbs  == NULL) {
        printf("ERROR cannot read problem file %s\n", probFile);
        exit(2);
    }
    fpProbsAux=fpProbs;

    //puts the user insput on a string to printed
    for (int i=1; i<argc; i++) UIsz=sizeof(char)*strlen(argv[i]) + UIsz + 1;
    userInput= (char*) malloc(UIsz);
    for (int i=1; i<argc; i++){
        strcat(userInput,argv[i]);
        strcat(userInput, " ");
    }
    //cicle to go through all maps
    for (int i=3; i<argc ; i++){
        
        openMapandOut(i, argv, fileout, mapFile, fpMaps, fpOut); //abre mapa retorna fpMaps e fpOut
         if(fpMaps!=NULL){
            createGraph(fpMaps, g);
            selectProblems(fpProbsAux, fpOut, g, opt, userInput);
            extractProbs(opt, fpProbs);

            fclose(fpMaps);
            fclose(fpOut);
        }
        if ((strcmp(opt, "-1oo") == 0) || (strcmp(opt, "-1ao") == 0)) break;
    }

    free(userInput);
    fclose(fpProbs);
    return 0;
}