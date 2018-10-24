#include <stdbool.h>
#include "RainbowTable.h"

#define nbReduction 50000

char* crackHash(RainbowTable* table, char* hash);
RainbowRow* search(RainbowTable* table, char* tail);
char* buildPwd(RainbowRow* row, char* hash, int passwordLength);
RainbowRow* testStep(RainbowTable* table, unsigned char* hash, int step);