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

    unsigned int memptr = 0;
    int offset;
    int oppositecounter;
    char currentchar;
    char inputchar; 

    for( int i = 0; i < file->contentssize; i++ ) {
        currentchar = *(file->contents + i);
        switch( currentchar ) {
            case '+':
                memarray[memptr]++;
                break;
            case '-':
                memarray[memptr]--;
                break;
            case '>':
                memptr < memsize - 1 ? (memptr++) : (memptr = 0);
                break;
            case '<':
                memptr > 0 ? (memptr--) : (memptr = memsize - 1);
                break;
            case '.':
                printf("%c", memarray[memptr]);
                break;
            case '[':
                offset = 0;
                oppositecounter = 0;
                if ( ((int)memarray[memptr]) == 0 ) {
                    while( 1 ) {
                        offset++;
                        if ( i + offset < file->contentssize ) {
                            currentchar = *(file->contents + (i + offset));
                        } else {
                            printf( "Error! found [ at characther %d but no matching ]. Something is wrong with your brainfuck program\n", i );
                            return -1;
                        }
                        if( currentchar == ']' ) {
                            if( oppositecounter == 0 ) {
                                i += offset + 1;
                                break;
                            } else {
                                printf( "%d", i + offset );
                                oppositecounter--;
                            }
                        } 
                        if( currentchar == '[' )
                            oppositecounter++;
                        
                    }
                }
                break;
            case ']':
                offset = 0;
                oppositecounter = 0;
                if ( ((int)memarray[memptr]) > 0 ) {
                    while( 1 ) {
                        offset++;
                        if ( i - offset - 1 > 0 ) {
                            currentchar = *(file->contents + (i - offset));
                        } else {
                            printf( "Error! found ] at character %d but no matching [. Something is wrong with your brainfuck program\n", i );
                            return -1;
                        }
                        if( currentchar == '[' ) {
                            if( oppositecounter == 0 ) {
                                i -= ( offset + 1 );
                                break;
                            } else {
                                oppositecounter--;
                            }
                        } 
                        if( currentchar == ']' ) 
                            oppositecounter++;
                        
                    }
                }
                break;
            case ',':
                scanf("%c", &inputchar);
                scanf("");
                memarray[memptr] = inputchar;
                break;
            default:
                break;
        }
    }

    return 0;
}