#pragma once

typedef struct bfFiles {
    char* contents;
    int contentssize;
} bfFile;

enum Errortype {
    fileOpeningError = 1,
    argumentError = 2,
    bracketError = 3
};

bfFile* getbffile( const char* filename ); // Found in filehandling.c
void printError( const char* Error, int errorCode ); // Found in main.c
void printHelp(); // Found in main.c