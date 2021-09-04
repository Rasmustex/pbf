#include <stdio.h>
#include <stdlib.h>
#include "../include/filehandling.h"

int main ( int argc, const char* argv[] ) {

    if ( argc != 2 ) {
        printf( "Error: invalid number of arguments.\n");
        return -1;
    }

    bfFile* file = getbffile( argv[1] ); // requested file in the argument 
    if ( file->contentssize == -1 ) {
        return -1;
    }

    int memsize = 1000;
    unsigned char memarray[memsize]; // create and initialize program mem
    for (int i = 0; i < memsize; i++ ) {
        memarray[i] = 0;
    }

    unsigned char* ptr = memarray;
    int neededopposites;
    char currentchar;
    char inputchar; 
    int offset;
    int oppositecounter;

    for( int i = 0; i < file->contentssize; i++ ) {
        currentchar = *(file->contents + i);
        switch( currentchar ) {
            case '+':
                ++*ptr;
                break;
            case '-':
                --*ptr;
                break;
            case '>':
                ptr < memarray + memsize - 1 ? (ptr++) : (ptr = memarray);
                break;
            case '<':
                ptr > memarray ? (ptr--) : (ptr = memarray + memsize - 1);
                break;
            case '.':
                putchar( *ptr );
                break;
            case '[':
                if( !(*ptr) ) {
                    neededopposites = 1;
                    while( neededopposites > 0 ) {
                        if( i < file->contentssize )
                            currentchar = *(file->contents + (++i));
                        else {
                            printf( "Error! brackets don't match! There is a [ but no matching ]\n" );
                            return -1;
                        }
                        if( currentchar == ']' ) 
                            neededopposites--;
                        else if( currentchar == '[' ) 
                            neededopposites++;
                    }
                }
                break;
            case ']':
                if( *ptr ) {
                    neededopposites = 1;
                    while( neededopposites > 0 ) {
                        if( i > 0 )
                            currentchar = *(file->contents + (--i));
                        else {
                            printf( "Error! brackets don't match! There is a ] but no matching [\n", i );
                            return -1;
                        }
                        if( currentchar == '[' )
                            neededopposites--;
                        else if( currentchar == ']' )
                            neededopposites++;                            
                    }
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

    return 0;
}