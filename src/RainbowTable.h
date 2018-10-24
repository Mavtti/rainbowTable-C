#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sizeT 100

typedef struct RainbowRow RainbowRow;
struct RainbowRow {
	unsigned char* head;
	unsigned char* tail;
	RainbowRow* next;
};

typedef struct RainbowTable RainbowTable;
struct RainbowTable{
	int tableSize;
	int passwordLength;
	RainbowRow* rows;
};

RainbowTable generateTable(int pL);
RainbowTable* findTable(char* fichier);
static unsigned char *randomHeadGenerator(unsigned char* str,size_t size);
unsigned char* tailGenerator(unsigned char* myHead);
unsigned char* reduction(unsigned char* hash, int index, int passwordLength);
unsigned char* hasher(unsigned char* reduction);
