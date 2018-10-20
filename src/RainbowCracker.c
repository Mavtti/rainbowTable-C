#include "RainbowTable.h"

char* crackHash(RainbowTable* table, char* hash) {
    RainbowRow* hashRow = NULL;
    for(int i = nbReduction; i >= 0; i--){
        hashRow = testStep(table, hash, i);
        if (hashRow != NULL) {
            break;
        }
    }
    if (hashRow != NULL) {
        return buildPwd(hashRow, hash);
    }
    return NULL;
}



RainbowRow* search(RainbowTable* table, char* tail) {
    RainbowRow* current = table -> rows;
    while (current -> next != NULL) {
        if (strcmp(current -> tail, tail) == 0) {
            return current;
        }
        current = current -> next;
    }
    return NULL;
}

RainbowRow* testStep(RainbowTable* table, char* hash, int step) {
    char* current = malloc(strlen(hash) * sizeof(char));
    strcpy(current, hash);

    for(int i = step; i < nbReduction; i++)
    {
        // Hash and reduce
    }

    // reduce hash one more time

    return search(table, current);
}

char* buildPwd(RainbowRow* row, char* hash) {
    char* currentHash = malloc(strlen(hash) * sizeof(char));
    char* currentPwd = malloc(strlen(row->head) * sizeof(char));
    strcpy(currentPwd, row ->head);
    // set currentHash to the hash of currentPwd

    for(size_t i = 0; i < nbReduction; i++)
    {
        if (strcmp(currentHash, hash) == 0) {
            break;
        }
        // set currentpwd to the reduction of currentHash
        // set currenthash to the hash of current pwd
    }

    return currentPwd;
}
