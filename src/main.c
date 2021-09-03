#include <stdio.h>
#include <stdlib.h>
#include "../include/filehandling.h"
#include <stdbool.h>

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
    bool rightBracketFound;
    bool leftBracketFound;
    int leftcounter;
    int rightcounter;
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
                rightBracketFound = false;
                offset = 0;
                leftcounter = 0;
                if ( ((int)memoryarray[memoryptr]) == 0 ) {
                    while( !rightBracketFound ) {
                        offset++;
                        if ( i + offset < file->contentssize ) {
                            currentchar = *(file->contents + (i + offset));
                        } else {
                            printf( "Error! found [ but no matching ]. Something is wrong with your brainfuck program\n" );
                            return -1;
                        }
                        if( currentchar == ']' ) {
                            if( leftcounter == 0 ) {
                                i += offset + 1;
                                rightBracketFound = true; 
                            } else {
                                printf( "%d", i + offset );
                                leftcounter--;
                            }
                        } 
                        if( currentchar == '[' ) {
                            leftcounter++;
                        }
                    }
                }
                break;
            case ']':
                leftBracketFound = false;
                offset = 0;
                rightcounter = 0;
                if ( ((int)memoryarray[memoryptr]) > 0 ) {
                    while( !leftBracketFound ) {
                        offset++;
                        if ( i - offset - 1 > 0 ) {
                            currentchar = *(file->contents + (i - offset));
                        } else {
                            printf( "Error! found ] but no matching [. Something is wrong with your brainfuck program\n" );
                            return -1;
                        }
                        if( currentchar == '[' ) {
                            if( rightcounter == 0 ) {
                                i -= ( offset + 1 );
                                leftBracketFound = true;
                            } else {
                                rightcounter--;
                            }
                        } 
                        if( currentchar == ']' ) {
                            rightcounter++;
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