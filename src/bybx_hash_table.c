#include<stdio.h>
#include<string.h>

#include"bybx_hash_table.h"

unsigned int bybx_hash(char* str, unsigned int range) {
    unsigned int hash = 0;
    unsigned int g = 31;
    for(unsigned int i = 0; i < strlen(str); ++i) {
        char c = str[i];
        hash += hash*g + c;
    }

    return hash%range;
}

bybx_HashTable bybx_hashTableCreate(unsigned int columns, size_t itemSize) {
    bybx_HashTable table = malloc(sizeof(bybx_HashTableData));
   
    table->itemSize = itemSize;
    table->length = 0;

    table->colummnsCount = columns;
    table->columns = malloc(sizeof(bybx_HashTableColumn)*columns);
    for(unsigned int i = 0; i < columns; ++i) {
        bybx_HashTableColumn* c = table->columns + i;     
        c->rows = malloc(sizeof(itemSize)*3);
        c->rowKeys = malloc(sizeof(char*)*3);
        c->rowsAllocated = 3;
        c->rowsLength = 0;
    }
    
    return table;
}

void bybx_hashTableFree(bybx_HashTable table) {
    for(unsigned int i = 0; i < table->colummnsCount; ++i) {
        bybx_HashTableColumn* c = table->columns + i;
        free(c->rows);
        free(c->rowKeys);
    }

    free(table->columns);
    free(table);
}

void bybx_hashTableSet(bybx_HashTable table, char* key, void* value) {
    unsigned int hashValue = bybx_hash(key, table->colummnsCount);
    bybx_HashTableColumn* c = table->columns + hashValue;

    bool keyFound = false;
    for(unsigned int i = 0; i < c->rowsLength; ++i) {
        char* k = c->rowKeys[i];
        if(strcmp(k, key) == 0) {
            keyFound = true;
            memcpy(((char*)c->rows) + i*table->itemSize, value, table->itemSize);
        }
    }

    if(!keyFound) {
        c->rowsLength++;
        if(c->rowsAllocated < c->rowsLength) {
            while(c->rowsAllocated < c->rowsLength) {
                c->rowsAllocated *= 2; 
            }

            c->rows = realloc(c->rows, sizeof(table->itemSize)*c->rowsAllocated);
            c->rowKeys = realloc(c->rows, sizeof(char*)*c->rowsAllocated);
        }
    
        c->rowKeys[c->rowsLength - 1] = key;
        memcpy(((char*)c->rows) + (c->rowsLength - 1)*table->itemSize, value, table->itemSize);
    } 
}

void* bybx_hashTableGet(bybx_HashTable table, char* key) {
    unsigned int hashValue = bybx_hash(key, table->colummnsCount);
    bybx_HashTableColumn* c = table->columns + hashValue;
    
    for(unsigned int i = 0; i < c->rowsLength; ++i) {
        char* k = c->rowKeys[i];
        if(strcmp(k, key) == 0) {
            return ((char*)c->rows) + i*table->itemSize;
        }
    }

    return NULL;
}

bool bybx_hashTableGetCopy(bybx_HashTable table, char* key, void* copyTo) {
    unsigned int hashValue = bybx_hash(key, table->colummnsCount);
    bybx_HashTableColumn* c = table->columns + hashValue;
    
    for(unsigned int i = 0; i < c->rowsLength; ++i) {
        char* k = c->rowKeys[i];
        if(strcmp(k, key) == 0) {
            if(copyTo == NULL) {
                return true;
            }
            memcpy(copyTo, ((char*)c->rows) + i*table->itemSize, table->itemSize);
            return true;
        }
    }

    return false;
}
