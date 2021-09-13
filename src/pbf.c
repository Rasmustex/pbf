#include <stdio.h>
#include <stdlib.h>
#include "../include/pbf.h"

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

void printError( const char* Error, int errorCode ) {
    printf("\033[0;31m");
    printf("Error: ");
    printf("\033[0m");
    printf( "%s\n", Error );
    exit(errorCode);
}