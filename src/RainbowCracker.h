#include <stdbool.h>
#include "RainbowTable.h"

#define nbReduction 50000

char* crackHash(RainbowTable* table, char* hash);
RainbowRow* search(RainbowTable* table, char* tail);
char* buildPwd(RainbowRow* row, char* hash);
RainbowRow* testStep(RainbowTable* table, char* hash, int step);