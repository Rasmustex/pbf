#ifndef PBF_H
#define PBF_H

#ifdef __cplusplus
extern "C" {
#endif

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
    void cleanUp( bfFile* file ); // Found in main.c
    void printHelp(); // Found in main.c

#ifdef __cplusplus
}
#endif
#endif