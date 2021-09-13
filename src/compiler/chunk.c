#include "chunk.h"
#include "comp_common.h"
#include "tools.h"

// disable "type name is not allowed" error
#ifdef __INTELLISENSE__
#pragma diag_suppress 254
#pragma diag_suppress 29
#endif

void initChunk(Chunk *chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->words = NULL;
    chunk->lines = NULL;
}

void writeChunk(Chunk *chunk, uint16_t word, int line)
{
    if (chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->words = GROW_ARRAY(
            uint16_t, chunk->words, chunk->capacity);
        chunk->lines = GROW_ARRAY(
            int, chunk->lines, chunk->capacity);
    }

    chunk->words[chunk->count] = word;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

void freeChunk(Chunk *chunk)
{
    FREE_ARRAY(uint16_t, chunk->words, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    initChunk(chunk);
}
