#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sizeT 5

typedef struct RainbowRow RainbowRow;
struct RainbowRow {
	char* head;
	char* tail;
	RainbowRow* next;
};

typedef struct RainbowTable RainbowTable;
struct RainbowTable{
	int tableSize;
	int passwordLength;
	RainbowRow* rows;
};

RainbowTable generateTable(int pL);
static char *randomHeadGenerator(char* str,size_t size);
char* tailGenerator(char* myHead);