#include "RainbowTable.h"

#define nbReduction 50000

RainbowRow* testStep(RainbowTable* table, unsigned char* hash, int step);
RainbowRow* search(RainbowTable* table, unsigned char* tail);
unsigned char* buildPwd(RainbowRow* row, unsigned char* hash, int passwordLength);

unsigned char* crackHash(RainbowTable* table, unsigned char* hash) {
    RainbowRow* hashRow = NULL;
    for(int i = nbReduction; i >= 0; i--){
        hashRow = testStep(table, hash, i);
        if (hashRow != NULL) {
            break;
        }
    }
    if (hashRow != NULL) {
        return buildPwd(hashRow, hash, table -> passwordLength);
    }
    return NULL;
}



RainbowRow* search(RainbowTable* table, unsigned char* tail) {
    RainbowRow* current = table -> rows;
    while (current -> next != NULL) {
        if (strcmp(current -> tail, tail) == 0) {
            return current;
        }
        current = current -> next;
    }
    return NULL;
}

RainbowRow* testStep(RainbowTable* table, unsigned char* hash, int step) { 
    unsigned char* current = malloc(strlen(hash) * sizeof(unsigned char));
    strcpy(current, hash);

    for(int i = step; i < nbReduction; i++)
    {
        current = hasher(reduction(current, i, table -> passwordLength));
    }
    
    current = reduction(hash, nbReduction, table -> passwordLength);


    return search(table, current);
}

unsigned char* buildPwd(RainbowRow* row, unsigned char* hash, int passwordLength) {
    unsigned char* currentHash = malloc(strlen(hash) * sizeof(unsigned char));
    unsigned char* currentPwd = malloc(strlen(row->head) * sizeof(unsigned char));
    strcpy(currentPwd, row ->head);

    currentHash = hasher(currentPwd);

    for(size_t i = 0; i < nbReduction; i++)
    {
        if (strcmp(currentHash, hash) == 0) {
            break;
        }
        // set currentpwd to the reduction of currentHash
        // set currenthash to the hash of current pwd
        currentPwd = reduction(currentHash, i, passwordLength);
        currentHash = hasher(currentPwd);
    }

    return currentPwd;
}
