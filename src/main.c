#include<stdio.h>
#include<stdlib.h>

#include "bybx_hash_table.h"
#include"bybx_list.h"

void printList(bybx_List list) {
	printf("------ Printing List ------\n");
	bybx_listLoop(list, int)
		printf("\t%d.\t%d\n", i, *pListItem);
	}
	printf("---------------------------\n");
}

void printTable(bybx_HashTable table) {
	printf("------ Printing Table -----\n");
	for(unsigned int i = 0; i < table->colummnsCount; ++i) {
		bybx_HashTableColumn column = table->columns[i];
		for(unsigned int j = 0; j < column.rowsLength; ++j) {
			int* pValue = ((int*)column.rows) + j;
			char** pKey = column.rowKeys + j; 
			printf("\t%s:\t%d\n", *pKey, *pValue);
		}
	}
	printf("---------------------------\n");
}

int main() {
	bybx_List list = bybx_listCreate(sizeof(int));

	int initialValues[6] = {
		1,
		7,
		3,
		-2,
		9,
		-5
	};
	bybx_listAppend(list, &initialValues, 6);

	printList(list);
	bybx_listFree(list);
	
	/*
	bybx_HashTable table = bybx_hashTableCreate(15, sizeof(int));
	
	int value1 = -2;
	bybx_hashTableSet(table, "Key 1", &value1);
	int value2 = 6;
	bybx_hashTableSet(table, "2 Key", &value2);
	int value3 = 9;
	bybx_hashTableSet(table, "Key 3", &value3);
	int value4 = -14;
	bybx_hashTableSet(table, "4 Key", &value4);
	int value5 = -4;
	bybx_hashTableSet(table, "Key 5", &value5);
	bybx_hashTableSet(table, "Key 3", &value1);

	printTable(table);
	
	int value5Copy;
	bybx_hashTableGetCopy(table, "Key 5", &value5Copy);
	printf("The key, Key 5 returns %d\n", value5Copy);

	int value3Copy = *((int*)bybx_hashTableGet(table, "Key 3"));
	printf("The key, Key 3 returns %d\n", value3Copy);

	bybx_hashTableFree(table);*/
	return 0;
}
