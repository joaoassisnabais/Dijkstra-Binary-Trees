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
//#include "problems.h"

int main (int argc, char *argv[]){

    FILE *fpProbs, *fpMaps = NULL;// *fpOut;
    char *opt, *probFile, *mapFile = NULL, *fileout = NULL, *prob = NULL;
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
    //fpProbs = fopen("test1/Pardais01/problemas01.prbs1", "r");
    if(fpProbs == NULL) {
        printf("ERROR cannot read problem file %s\n", probFile);
        exit(2);
    }
    
    //cicle to go through all maps
    for (int i=3; i<argc ; i++){
        
        openMapandOut(i, argv, fileout, mapFile, fpMaps);
        extractProbs(fpProbs, opt, prob);
        createGraph(fpMaps, g);



        if(fpMaps !=NULL) fclose(fpMaps);
        free(fileout);
        if ((strcmp(opt, "-1oo") == 0) || (strcmp(opt, "-1ao") == 0)) break;
    }

    fclose(fpProbs);
    return 0;
}