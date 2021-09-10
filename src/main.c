#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "../include/pbf.h"

void printError( const char* Error, int errorCode ) {
    printf("\033[0;31m");
    printf("Error: ");
    printf("\033[0m");
    printf( "%s\n", Error );
    exit(errorCode);
}

void cleanUp( bfFile* file ) { // Safety cleanup to make sure nothing is left behind (although the OS should take care of it)
    free( file->contents );
    free( file );
}

void printHelp() {
    printf("Usage: pbf [OPTIONS] <filename>...\n");
    printf("\n");
    printf("pbf is a simple brainfuck interpreter.\n");
    printf("To run a brainfuck file with the defaults, run pbf <filename>.\n");
    printf("\n");
    printf("Options:\n");
    printf("    -s <arraysize>  specify memory array size. Defaults to 1000 cells.\n");
    printf("    -e <string>     evaluates the input string as a brainfuck program.\n");
    printf("    -h              show help.\n");
}

int main ( int argc, char** argv ) {

    if ( argc < 2 ) {
        printHelp();
        printError( "Invalid number of arguments", argumentError );
    }

    int eflag = 0;
    int option;
    int memsize = 1000;
    bfFile* file; 

    // Handle command line arguments
    while( ( option = getopt(argc, argv, "hs:e:" ) ) != -1 ) {
        switch ( option ) {
            case 'h':
                printHelp();
                exit(0);
                break;
            case 'e': 
                // Create a brainfuck "file" from the input string/the next argument. Will be run instead of an actual file
                eflag++;
                file = (bfFile*)malloc( sizeof( bfFile) );
                file->contentssize = strlen( optarg );
                file->contents = (char*)malloc( file->contentssize + 1 );
                strcpy( file->contents, optarg ); 
                break;
            case 's':
                // Specify memory size
                memsize = atoi(optarg);
                break;
            default:
                break;
        }
    }

    // if eflag is set, we should not get a bf file. If it isn't, we open the first thing that isn't a recognized option
    if(!eflag) 
        file = getbffile( argv[optind] ); // requested file in the argument 

    unsigned char memarray[memsize]; // create and initialize program memory
    for (int i = 0; i < memsize; i++ ) {
        memarray[i] = 0;
    }

    unsigned char* ptr = memarray;
    int neededopposites; // Counter of how many opposites are needed for a jump to stop after encountering a bracket
    char currentchar; // The current selected character in the brainfuck program
    char inputchar; 

    for( int i = 0; i < file->contentssize; i++ ) {
        currentchar = *(file->contents + i);
        switch( currentchar ) {
            case '+':
                ++*ptr;
                break;
            case '-':
                --*ptr;
                break;
            case '>': // Move ptr in positive direction if below max pointer value, else, wrap around
                ptr < memarray + memsize - 1 ? (ptr++) : (ptr = memarray);
                break;
            case '<': // Move ptr in negative direction if above min pointer value, else, wrap around
                ptr > memarray ? (ptr--) : (ptr = memarray + memsize - 1);
                break;
            case '.':
                putchar( *ptr );
                break;
            case '[':
                if( !(*ptr) ) {
                    neededopposites = 1; // We need to find one right bracket to break out 
                    while( neededopposites > 0 ) {
                        if( i < file->contentssize )
                            currentchar = *(file->contents + (++i));
                        else {
                            // We have reached EOF without finding the matching bracket
                            cleanUp( file );
                            printError( "Brackets don't match! There is a [ but no matching ]", bracketError );
                        }
                        if( currentchar == ']' ) // If found, we need one less ] to get out of loop
                            neededopposites--;
                        else if( currentchar == '[' ) // We found another [, meaning we need to find more ]'s before finding the right one
                            neededopposites++;
                    }
                }
                break;
            case ']':
                if( *ptr ) {
                    // Same thing as above, but we go backwards and search for [
                    neededopposites = 1;
                    while( neededopposites > 0 ) {
                        if( i > 0 )
                            currentchar = *(file->contents + (--i));
                        else {
                            cleanUp( file );
                            printError( "Brackets don't match! There is a ] but no matching [", bracketError );
                        }
                        if( currentchar == '[' )
                            neededopposites--;
                        else if( currentchar == ']' )
                            neededopposites++;                            
                    }
                    // Decrement by 1 so we land on the [ after i is incremented at beginning of loop
                    i--; 
                }
                break;
            case ',':
                *ptr = getchar();
                break;
            default:
                break;
        }
    }
    cleanUp( file );
    return 0;
}