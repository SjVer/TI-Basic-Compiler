#ifndef TI_CHUNK_H
#define TI_CHUNK_H

#include "common.h"

// chunk stuff
typedef struct
{
    int count;
    int capacity;
    uint16_t *words;
    int *lines;
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint16_t word, int line);
void freeChunk(Chunk *chunk);

#endif