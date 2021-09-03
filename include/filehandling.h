#pragma once

typedef struct bfFiles {
    char contents[10000];
    int contentssize;
} bfFile;

bfFile* getbffile( const char* filename );
