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

    unsigned char memoryarray[1000]; // create and initialize program memory
    for (int i = 0; i < 1000; i++ ) {
        memoryarray[i] = 0;
    }

    unsigned int memoryptr = 0;
    int offset;
    int oppositecounter;
    char currentchar;
    char inputchar; 

    for( int i = 0; i < file->contentssize; i++ ) {
        currentchar = *(file->contents + i);
        switch( currentchar ) {
            case '+':
                memoryarray[memoryptr]++;
                break;
            case '-':
                memoryarray[memoryptr]--;
                break;
            case '>':
                if( memoryptr < 999 ) {
                    memoryptr++;
                } else {
                    memoryptr = 0;
                }
                break;
            case '<':
                if( memoryptr > 0 ) {
                    memoryptr--;
                } else {
                    memoryptr = 999;
                }
                break;
            case '.':
                printf("%c", memoryarray[memoryptr]);
                break;
            case '[':
                offset = 0;
                oppositecounter = 0;
                if ( ((int)memoryarray[memoryptr]) == 0 ) {
                    while( 1 ) {
                        offset++;
                        if ( i + offset < file->contentssize ) {
                            currentchar = *(file->contents + (i + offset));
                        } else {
                            printf( "Error! found [ but no matching ]. Something is wrong with your brainfuck program\n" );
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
                        if( currentchar == '[' ) {
                            oppositecounter++;
                        }
                    }
                }
                break;
            case ']':
                offset = 0;
                oppositecounter = 0;
                if ( ((int)memoryarray[memoryptr]) > 0 ) {
                    while( 1 ) {
                        offset++;
                        if ( i - offset - 1 > 0 ) {
                            currentchar = *(file->contents + (i - offset));
                        } else {
                            printf( "Error! found ] but no matching [. Something is wrong with your brainfuck program\n" );
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
                        if( currentchar == ']' ) {
                            oppositecounter++;
                        }
                    }
                }
                break;
            case ',':
                scanf("%c", &inputchar);
                scanf("");
                memoryarray[memoryptr] = inputchar;
                break;
            default:
                break;
        }
    }

    return 0;
}