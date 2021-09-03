#pragma once

typedef struct bfFiles {
    char* contents;
    int contentssize;
} bfFile;

bfFile* getbffile( const char* filename );
