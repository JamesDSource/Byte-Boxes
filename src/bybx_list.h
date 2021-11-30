#ifndef __BYBX_LIST__
#define __BYBX_LIST__

#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

#define bybx_listLoop(list, type) \
    bybx_List l = (list); \
    for(unsigned int i = 0; i < l->length*l->itemSize; i += l->itemSize) { \
        type* pListItem = (type*)((char*)l->items + i);

#define bybx_listLoopReverse(list, type) \
    bybx_List l = (list); \
    for(unsigned int i = l->length*l->itemSize; i >= 0; i -= l->itemSize) { \
        type* pListItem = (type*)((char*)l->items + i);

#define bybx_listLoopRange(list, type, start, end) /* End is exclusive */ \
    bybx_List l = (list); \
    unsigned int s = (start), e = (end); \
    for(unsigned int i = l->itemSize*s; i < l->itemSize*e; i += l->itemSize) { \
        type* pListItem = (type*)((char*)l->items + i);

typedef struct {
    void* items;
    size_t itemSize;
    unsigned int allocated;
    unsigned int length;
} bybx_ListData;

typedef bybx_ListData* bybx_List;

bybx_List bybx_listCreate(size_t itemSize);
unsigned int bybx_listAppend(bybx_List list, void* value, unsigned int count);
unsigned int bybx_listInsert(bybx_List list, unsigned int index, void* value, unsigned int count);
unsigned int bybx_listRemove(bybx_List list, unsigned int index, unsigned int count);
void bybx_listPop(bybx_List list, void* copyTo);
void bybx_listClear(bybx_List list);

void bybx_listSet(bybx_List list, unsigned int index, void* value);
void* bybx_listGet(bybx_List list, unsigned int index);
void bybx_listGetCopy(bybx_List list, unsigned int index, void* copyTo);

bool bybx_listFind(bybx_List list, void* value, unsigned int* index, unsigned int number);
unsigned int bybx_listCount(bybx_List list, void* value);
void bybx_listFree(bybx_List list);
#endif
