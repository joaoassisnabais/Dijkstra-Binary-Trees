/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   fileData.h
 *
 ******************************************************************************/

#ifndef FILE_DATA_H
#define FILE_DATA_H
#include "graphs.h"
#include "binaryTree.h"

typedef struct lista_problemas probs;
struct lista_problemas {
    char problema[3];
    int va;
    int vb;
    int k;
    char id;
    double cost;
    probs* next;
};


probs* extractProbs (char* opt, FILE* fp);
void openMapandOut(char* mapFile, FILE** fpMaps, FILE** fpout);
void selectProblems(probs* headProbs, FILE* fpout, data* g);
void freeProbs(probs *p);
#endif
