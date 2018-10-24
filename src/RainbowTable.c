#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "sha256.h"


#define sizeT 500
#define nbReduction 50000

const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";

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
	int redCount;
	RainbowRow* rows;
};

RainbowTable generateTable(int pL);
static unsigned char *randomHeadGenerator(unsigned char* str,size_t size);
unsigned char* tailGenerator(unsigned char* myHead, int passwordLength);
unsigned char* reduction(unsigned char* hash, int index, int passwordLength);
unsigned char* hasher(unsigned char* reduction);

// Creates a RainbowTable variable
RainbowTable generateTable(int pL){
	RainbowTable myTable;
	myTable.rows = NULL;
	myTable.passwordLength = pL;
	myTable.tableSize = sizeT;
	myTable.redCount = nbReduction;
	int i = 0;
	for(i=0 ; i<sizeT; i++){
		RainbowRow* row = (RainbowRow *)malloc(sizeof(RainbowRow));
		row->head = (unsigned char*)malloc(pL * sizeof(unsigned char));
		row->head = randomHeadGenerator(row->head, pL);
		row->tail = tailGenerator(row->head, pL);
		row->next = myTable.rows;
		myTable.rows = row;
	}
	return myTable;
}

/*"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" full charset to be set*/

unsigned char* tailGenerator(unsigned char* myHead, int passwordLength){
	unsigned char * current = malloc(sizeof(unsigned char) * passwordLength);
	unsigned char * tobeFreed = malloc(sizeof(unsigned char) * passwordLength);
	strcpy(current, myHead);
	for(size_t i = 0; i <= nbReduction; i++)
	{
		tobeFreed = current;
		current = hasher(current);
		free(tobeFreed);
		tobeFreed = current;
		current = reduction(current, i, passwordLength);
		free(tobeFreed);
	}
	return current;
}

static unsigned char *randomHeadGenerator(unsigned char* str, size_t size){
	
    if (size) {	
        for (size_t n = 0; n < size; n++) {
					int key = rand() % (int) (strlen(charset) - 1);
					str[n] = charset[key];
			  }
			  str[size] = '\0';
		}
    return str;
}

// Generates a Rainbow.txt file in which the RainbowTable will be stored
void createFile(RainbowTable table){
	FILE *f = fopen("Rainbow.txt", "w");
	RainbowRow* current;
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	/* print table info */
	/*fprintf(f, "### Rainbow table information ###\n");*/
	fprintf(f, "%d <- Table size\n", table.tableSize);
	fprintf(f, "%d <- Password length\n", table.passwordLength);
	fprintf(f, "%d <- Reduction count\n\n", table.redCount);

	/* print table data */
	current = table.rows;
	while(current != NULL){
		fprintf(f,"%s %s\n",current->head,current->tail);
		current = current->next;
	}
	fclose(f);
}

unsigned char* reduction(unsigned char* hash, int index, int passwordLength) {
	long long int entier = 0;
	
	for(size_t i = 0; i < 30; i++) {
		entier += (long long int) hash[i] * pow(2, i);
	}
	entier = (entier + (long long int) index) % ((long long int) pow(36, 8));
	int j = passwordLength - 1;
	unsigned char* reduction = malloc(passwordLength * sizeof(unsigned char));
	for(int k = 0; k < passwordLength; k++) {
		reduction[k] = 'a';
	}

	while (entier > 0 && j >= 0) {
		reduction[j] = charset[(int) entier % strlen(charset)];
		entier /= strlen(charset);
		j--;
	}
	return reduction;
}

unsigned char* hasher(unsigned char* reduction) {
	SHA256_CTX ctx;
	unsigned char *hash = malloc(SHA256_BLOCK_SIZE);
	sha256_init(&ctx);
	sha256_update(&ctx, reduction ,strlen(reduction));
	sha256_final(&ctx, hash);
	return hash;
}

RainbowTable* findTable(char* fichier){
	RainbowTable table;
	RainbowTable* pTable = &table;
	int info;
	char line [80];
	
	table.rows = NULL;
	FILE *f = fopen("Rainbow.txt", "r");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	/* Read table information */
	fscanf(f,"%d",&info);
	table.tableSize =  info;
	fgets(line,79,f);
	fscanf(f,"%d",&info);
	table.passwordLength =  info;
	fgets(line,79,f);
	fscanf(f,"%d",&info);
	table.redCount =  info;
	
	/* Read table datas */
	while(fgets(line,79,f) != NULL){
		
		RainbowRow* row = (RainbowRow *)malloc(sizeof(RainbowRow));
		unsigned char* myHead = (unsigned char *)malloc(sizeof(unsigned char)*table.passwordLength) ;
		unsigned char* myTail = (unsigned char *)malloc(sizeof(unsigned char)*table.passwordLength) ;
		fscanf(f,"%s %s",myHead, myTail);
		row->head =  myHead;
		row->tail = myTail;
		row->next = table.rows;
		table.rows = row;
	}
	
	fclose(f);
	return pTable;
}

void printRainbow(RainbowTable* table){
	printf( "%d <- Table size\n", table->tableSize);
	printf( "%d <- Password length\n", table->passwordLength);
	printf( "%d <- Reduction count\n\n", table->redCount);
	RainbowRow* current = table->rows;
	while( current != NULL){
		printf("%s %s\n",current->head,current->tail);
		current = current->next;
	}
}

void freeList(struct RainbowRow* head){
   struct RainbowRow* tmp;
   while (head != NULL){
       tmp = head;
       head = head->next;
       free(tmp);
			 tmp = NULL;
  }
}
