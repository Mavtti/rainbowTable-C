#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "sha256.h"

#define sizeT 5
#define nbReduction 1

// "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"      full charset to implement
const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";


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
char* reduction(char* hash, int index, int passwordLength);
char* hash(char* reduction);
void createFile(RainbowTable table);
