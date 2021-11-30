#include<stdio.h>
#include<string.h>

#include"bybx_list.h"

// Allocates a list and it's items
bybx_List bybx_listCreate(size_t itemSize) {
    // Initialize the items
    bybx_List list = malloc(sizeof(bybx_ListData));
    list->itemSize = itemSize;    
    list->allocated = 3;

    list->items = malloc(itemSize*list->allocated);
    list->length = 0;
    return list;
}

// Appends a new item on the end of the list
unsigned int bybx_listAppend(bybx_List list, void* value, unsigned int count) {
    list->length += count;
    
    // Resize list if needed
    if(list->allocated < list->length) {
        do {
            list->allocated *= 2;
        } while(list->allocated < list->length);
        list->items = realloc(list->items, (list->itemSize)*(list->allocated));
    }

    // Add the new values
    void* dst = ((char*)list->items) + list->itemSize*(list->length - count); 
    memcpy(dst, value, list->itemSize*count);
    return list->length;
}

unsigned int bybx_listInsert(bybx_List list, unsigned int index, void* value, unsigned int count) {
    if(index > list->length) {
        printf("ERROR in bybx_listInsert: Index %d is out of range\n", index);
        return list->length;
    }
    
    list->length += count;
    
    // Resize list if needed
    if(list->allocated < list->length) {
        do {
            list->allocated *= 2;
        } while(list->allocated < list->length);
        list->items = realloc(list->items, (list->itemSize)*(list->allocated));
    }

    
    if(index < list->length) { 
        // Shifting values forward
        void* shiftSrc = ((char*)list->items) + list->itemSize*index; 
        void* shiftDst = ((char*)list->items) + list->itemSize*(index + count);
        memmove(shiftDst, shiftSrc, list->itemSize*(list->length - count - index));
    }
    // Add the new values at the specified index
    void* dst = ((char*)list->items) + list->itemSize*index; 
    memcpy(dst, value, list->itemSize*count);
    return list->length;
}

// Removes an item from a list
unsigned int bybx_listRemove(bybx_List list, unsigned int index, unsigned int count) {
    if(index + count > list->length) {
        printf("ERROR in bybx_listRemove: Indicies %d-%d is out of range\n", index, index + count);
        return list->length;
    }

    // Shifting values backwords
    void* shiftSrc = ((char*)list->items) + list->itemSize*(index + count); 
    void* shiftDst = ((char*)list->items) + list->itemSize*index;
    memmove(shiftDst, shiftSrc, list->itemSize*(list->length - count - index));

    list->length -= count;
    // Resize list if needed
    if(list->allocated%2 == 0 && list->length < list->allocated/2) {
        do {
            list->allocated /= 2;
        } while(list->allocated%2 == 0 && list->length < list->allocated/2);
        list->items = realloc(list->items, list->allocated);
    }
    return list->length;
}

// Copies last item in list then removes it
void bybx_listPop(bybx_List list, void* copyTo) {
    if(list->length == 0) {
        return;
    }
    
    void* src = ((char*)list->items) + list->itemSize*(list->length - 1);
    memcpy(copyTo, src, list->itemSize);
    
    list->length--;
    if(list->allocated%2 == 0 && list->length < list->allocated/2) {
        list->allocated /= 2;
        list->items = realloc(list->items, list->allocated);
    }
}

void bybx_listClear(bybx_List list) {
    list->length = 0;
    
    // Resize list if needed
    if(list->allocated%2 == 0 && list->length < list->allocated/2) {
        do {
            list->allocated /= 2;
        } while(list->allocated%2 == 0 && list->length < list->allocated/2);
        list->items = realloc(list->items, list->allocated);
    }
}


void bybx_listSet(bybx_List list, unsigned int index, void* value) {
    if(index >= list->length) {
        printf("ERROR in bybx_listSet: Index %d is out of range\n", index);
        return;
    }

    void* dst = ((char*)list->items) + list->itemSize*index; 
    memcpy(dst, value, list->itemSize);
}

// Gets a pointer to a value at the index
void* bybx_listGet(bybx_List list, unsigned int index) {
    if(index >= list->length) {
        printf("ERROR in bybx_listGet: Index %d is out of range\n", index);
        return NULL;
    }

    void* value = ((char*)list->items) + list->itemSize*index;
    return value;
}

// Copies a value to a pointer
void bybx_listGetCopy(bybx_List list, unsigned int index, void* copyTo) {
    if(index < 0 || index >= list->length) {
        printf("ERROR in bybx_listGetCopy: Index %d is out of range\n", index);
        return;
    }

    void* src = ((char*)list->items) + list->itemSize*index;
    memcpy(copyTo, src, list->itemSize);
}

bool bybx_listFind(bybx_List list, void* value, unsigned int* index, unsigned int number) {
    for(unsigned int i = 0; i < list->length; ++i) {
        void* item = ((char*)list->items) + list->itemSize*i;
        if(memcmp(item, value, list->itemSize) == 0) {
            if(number == 0) {
                *index = i;
                return true;
            }
            number--;
        }
    }
    return false;
}

unsigned int bybx_listCount(bybx_List list, void* value) {
    unsigned int count = 0;
    for(unsigned int i = 0; i < list->length; ++i) {
        void* item = ((char*)list->items) + list->itemSize*i;
        if(memcmp(item, value, list->itemSize) == 0) {
            count++;
        }
    }
    return count;
}

// Frees the list and it's items
void bybx_listFree(bybx_List list) {
    free(list->items);
    free(list);
}
