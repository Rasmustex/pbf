#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/pbf.h"

bfFile* getbffile( const char* filename ) {
    bfFile* file = (bfFile*)malloc( sizeof( bfFile ) );
    FILE *f;
  
    if(!access( filename, F_OK )) {
        f = fopen(filename, "rb" );
    } else{
        free( file );
        printError( "Couldn't access the given file", fileOpeningError );
    }

    fseek( f, 0, SEEK_END ); // go to the end of the file stream
    long fsize = ftell(f); // get current position in the file stream. As we are at the end, this will be the final character
    fseek( f, 0, SEEK_SET ); // get back to the beginning
    
    char* string = (char*)malloc( fsize + 1 ); // allocate a string big enough for file contents on the heap
    fread( string, 1, fsize, f ); // read the entire file, where each element is one byte, and where there are fsize elements, in the file f, and put into string
    fclose( f );

    string[fsize] = 0;
    file->contents = (char*)malloc( fsize + 1 );

    file->contentssize = fsize;
    strcpy( file->contents, string );
    
    free( string );
    return file;     
}