/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   main.c
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"

int main (int argc, char *argv[]){

    FILE *fpProbs, *fpMaps, *fpOut;
    char *opt, *probFile, *mapFile, *fileout, *prob = NULL;  
    graph *g;
    g = (graph*) malloc(sizeof(graph));

    if(argc<4){
        printf("Not enough arguments \n");
        exit(0);
    }

    //extracting cmd line arguments without any map     
    opt = argv[1];
    probFile = argv[2];

    fpProbs = fopen(probFile, "r");
    if(fpProbs == NULL) {
        printf("ERROR cannot read problem file %s\n", probFile);
        exit(2);
    }
    
    //cicle to go through all maps
    for (int i=3; i<argc ; i++){
        
        iniMap(i, argv, fileout, mapFile, fpMaps);
        extractProbs ( fpProbs, opt, prob );



        if(fpMaps !=NULL) fclose(fpMaps);
        free(fileout);
        if ((strcmp(opt, "-1oo") == 0) || (strcmp(opt, "-1ao") == 0)) break;
    }


    

    fclose(fpProbs);
    return 0;
}