/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   fileData.h
 *
 ******************************************************************************/

#ifndef FILE_DATA_H
#define FILE_DATA_H

typedef struct probs {
    char problema[3];
    int vertice;
    int verticeOrK;//segundo input: vertice ou distancia (k)
    probs* next;
} probs;


probs * extractProbs (char* opt, FILE* fp);
void openMapandOut(int i, char* argv[], char* fileout, char* mapFile, FILE *fpMaps, FILE* fpout);
void selectProblems(probs* headProbs, FILE* fpout, graph* g, char* option, char* UI);
void printexit(FILE* fpout, char* out, char* UI);
#endif
