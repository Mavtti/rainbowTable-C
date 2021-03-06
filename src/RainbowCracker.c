#include "RainbowTable.h"
#include <stdbool.h>

#define nbReduction 50000

RainbowRow* testStep(RainbowTable* table, unsigned char* hash, int step);
RainbowRow* search(RainbowTable* table, unsigned char* tail);
unsigned char* buildPwd(RainbowRow* row, unsigned char* hash, int passwordLength);

bool compareHash(unsigned char* hash1, unsigned char* hash2, int taille) {
    for(int i = 0; i < taille; i++)
    {
        if (hash1[i] != hash2[i]) {
            return false;
        }
    }
    
    for(int i = 0; i < taille; i++)
    {
        printf("comparison %u, %u\n", hash1[i], hash2[i]);
    }
    
    return true;
}

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
        if (compareHash(current -> tail, tail, 8)) {
            return current;
        }
        current = current -> next;
    }
    return NULL;
}

RainbowRow* testStep(RainbowTable* table, unsigned char* hash, int step) { 
    unsigned char* current = malloc(32 * sizeof(unsigned char));
    unsigned char* tobeFreed = malloc(32 * sizeof(unsigned char));
    if (step % 1000 == 0) printf("Step %i \n", step);
    memcpy(current, hash, 32);

    for(int i = step; i < nbReduction; i++)
    {
		tobeFreed = current;
		current = reduction(current, i, table -> passwordLength);
		free(tobeFreed);
		tobeFreed = current;
		current = hasher(current);
		free(tobeFreed);
    }
    tobeFreed = current;
    current = reduction(current, nbReduction, table -> passwordLength);
    free(tobeFreed);
    RainbowRow* row = search(table, current);
    free(current);
    return row;
}

unsigned char* buildPwd(RainbowRow* row, unsigned char* hash, int passwordLength) {
    unsigned char* currentHash = malloc(strlen(hash) * sizeof(unsigned char));
    unsigned char* currentPwd = malloc(strlen(row->head) * sizeof(unsigned char));
    strcpy(currentPwd, row ->head);

    currentHash = hasher(currentPwd);

    for(size_t i = 0; i < nbReduction; i++)
    {
        if (compareHash(currentHash, hash, 32)) {
            break;
        }
        currentPwd = reduction(currentHash, i, passwordLength);
        currentHash = hasher(currentPwd);
    }

    
    for(int i = 0; i < 32; i++)
    {
        printf("%u, ", currentHash[i]);
    }
    
    return currentPwd;
}

