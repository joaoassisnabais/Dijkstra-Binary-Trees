/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   fileData.h
 *
 ******************************************************************************/

#ifndef FILE_DATA_H
#define FILE_DATA_H

void extractProbs ( FILE* fp, char* option, char* prob );
void openMapandOut(int i, char* argv[], char* fileout, char* mapFile, FILE *fpMaps, FILE* fpout);
void selectProblems(FILE* fpProbs, FILE* fpout, graph* g, char* option, char* UI);
void printexit(FILE* fpout, char* out, char* UI);
#endif
