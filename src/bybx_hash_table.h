#ifndef __BYBX_HASH_TABLE__
#define __BYBX_HASH_TABLE__

#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    void* rows;
    char** rowKeys;
    unsigned int rowsAllocated;
    unsigned int rowsLength;
} bybx_HashTableColumn;

typedef struct {
    bybx_HashTableColumn* columns;
    unsigned int colummnsCount;
    size_t itemSize;
    unsigned int length;
} bybx_HashTableData;

typedef bybx_HashTableData* bybx_HashTable;

unsigned int bybx_hash(char* str, unsigned int range);

bybx_HashTable bybx_hashTableCreate(unsigned int columns, size_t itemSize);
void bybx_hashTableFree(bybx_HashTable table);

void bybx_hashTableSet(bybx_HashTable table, char* key, void* value);
void* bybx_hashTableGet(bybx_HashTable table, char* key);
bool bybx_hashTableGetCopy(bybx_HashTable table, char* key, void* copyTo);
#endif
