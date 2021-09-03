#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/filehandling.h"

bfFile* getbffile( const char* filename ) {
    bfFile* file = (bfFile*)malloc( sizeof( bfFile ) );
    file->contentssize = -1; // Default value. If not overwritten, we know something has gone wrong, and we can exit with an error

    FILE *f = fopen(filename, "rb" ); // open the file
    if( f == NULL ) {
        printf( "Error: couldn't open file" );
        fclose( f );
        return file;
    }
    fseek( f, 0, SEEK_END ); // go to the end of the file stream
    long fsize = ftell(f); // get current position in the file stream. As we are at the end, this will be the final character
    fseek( f, 0, SEEK_SET ); // get back to the beginning
    
    char* string = (char*)malloc( fsize + 1 ); // allocate a string big enough for file contents on the heap
    fread( string, 1, fsize, f ); // read the entire file, where each element is one byte, and where there are fsize elements, in the file f, and put into string
    fclose( f );

    string[fsize] = 0;
    file->contents = (char*)malloc( fsize + 1 );

    // if( fsize > 10000 ) {
    //     printf( "Error: File is too long" );
    //     return file;
    // }

    file->contentssize = fsize;
    strcpy( file->contents, string );
    
    free( string );
    return file;     
}