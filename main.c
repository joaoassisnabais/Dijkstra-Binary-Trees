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

    FILE *fpProbs, *fpMaps = NULL, *fpOut = NULL;
    char *opt, *probFile, *mapFile = NULL, *fileout = NULL, *userInput = NULL;
    int UIsz=0;
    graph *g;
    g = (graph*) malloc(sizeof(graph));
    probs* problems;

    /*Number of cmd line arguments verification*/
    if(argc<4){
        printf("Not enough arguments \n");
        exit(1);
    }
    /*Extract cmd line arguments (option and problem file)*/
    opt = argv[1];
    probFile = argv[2];
    /*Open problems file*/
    fpProbs = fopen(probFile, "r");
    if(fpProbs  == NULL) {
        printf("ERROR cannot read problem file %s\n", probFile);
        exit(2);
    }
    /*User input into string*/
    for (int i=1; i<argc; i++) UIsz=sizeof(char)*strlen(argv[i]) + UIsz + 1;
    userInput= (char*) malloc(UIsz);
    for (int i=1; i<argc; i++){
        strcat(userInput,argv[i]);
        strcat(userInput, " ");
    }
    /*Cicle to go through all maps*/
    for (int i=3; i<argc ; i++){
        /*Open map and outputs file & create graph with map data*/
        openMapandOut(i, argv, mapFile, &fpMaps, &fpOut);
        createGraph(fpMaps, g);
        /*Store problems file's data & sellect and call problem funtion*/
        problems = extractProbs(opt, fpProbs);
        selectProblems(problems, fpOut, g, userInput);
        /*Close map and output files*/
        fclose(fpMaps);
        fclose(fpOut);
        /*Run only once depending on the option chosen*/
        if ((strcmp(opt, "-1oo") == 0) || (strcmp(opt, "-1ao") == 0)) break;
    }
    
    free(userInput);
    fclose(fpProbs);
    return 0;
}