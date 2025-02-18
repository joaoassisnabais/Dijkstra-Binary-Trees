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
#include "binaryTree.h"

int main (int argc, char *argv[]){

    FILE *fpProbs, *fpMaps = NULL, *fpOut = NULL;
    char *opt, *probFile;
    //graph *g;
    data *g;
    probs* problems;
    
    g = (data*) malloc(sizeof(data));

    /*Number of cmd line arguments verification*/
    if(argc != 4){
        printf("Not enough arguments: %d\n", argc);
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
    
    /*Store problems file's data*/
    problems = extractProbs(opt, fpProbs);
    fclose(fpProbs);
    /*Open map and outputs file*/
    openMapandOut(argv[3], &fpMaps, &fpOut);
    fprintf(fpOut, "%s %s %s\n\n", argv[1], argv[2], argv[3]);
    
    /*Cicle to go through all maps*/
    while(fscanf(fpMaps,"%d %d", &g->nv, &g->na) != EOF) {
        /*Create graph with map data*/
        CreateGraphBT(&fpMaps, g);
        /*Select and call problem funtion & free memory used*/
        selectProblems(problems, fpOut, g);
        //freeGraph(g);
        CleanMem(g->table,g->nv);

        /*Run only once depending on the option chosen*/
        if ((strcmp(opt, "-1oo") == 0) || (strcmp(opt, "-1ao") == 0)) break;
    }

    /*Close map, problems and output files*/
    probFree(problems);
    free(g);
    fclose(fpMaps);
    fclose(fpOut);
    return 0;
}