#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define sizeT 50000

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

RainbowTable generateTable(int pL){
	RainbowTable myTable;
	myTable.rows = NULL;
	myTable.passwordLength = pL;
	myTable.tableSize = sizeT;
	RainbowRow* nextRow ;
	int i = 0;

	for(i=0 ; i<sizeT; i++){
		RainbowRow* row = (RainbowRow *)malloc(sizeof(RainbowRow));
		char* myHead = (char *)malloc(sizeof(char)*pL) ;
		strcpy(myHead,randomHeadGenerator(myHead, pL));
		char* myTail = tailGenerator(myHead);
		row->head =  myHead;
		row->tail = myTail;
		row->next = myTable.rows;
		myTable.rows = row;
	}

	return myTable;
}

/*"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" full charset to be set*/

char* tailGenerator(char* myHead){
	return "oups";
}

static char *randomHeadGenerator(char* str, size_t size){
    const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
	
    if (size) {	
        for (size_t n = 0; n < size; n++) {
		int key = rand() % (int) (sizeof charset - 1);
		str[n] = charset[key];
        }
        str[size] = '\0';
    }
    
    return str;
}

void createFile(RainbowTable table){
	FILE *f = fopen("Rainbow1.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	/* print table info */
	fprintf(f, "### Rainbow table information ###\n");
	fprintf(f, "Table size: %d\n", table.tableSize);
	fprintf(f, "Password length: %d\n\n", table.passwordLength);
	fprintf(f, "### Rainbow table datas ###\n");

	/* print table data */
	RainbowRow* current = table.rows;
	while(current != NULL){
		fprintf(f,"%s %s\n",current->head,current->tail);
		current = current->next;
	}
	fclose(f);
}



// int main(int argc, char* argv[]){
// 	clock_t begin0 = clock();
// 	printf("Start Program ...\n");
// 	printf("Creating table of size : %d ...\n",sizeT);
// 	RainbowTable table = generateTable(8);
// 	clock_t end = clock();
// 	clock_t begin1 = clock();
// 	double time_spent = (double)(end - begin0) / CLOCKS_PER_SEC;
// 	printf("Table creation time: %d\n",time_spent);
// 	printf("Creation completed ...\n");
// 	printf("File creation ...\n");
// 	createFile(table);
// 	end = clock();
// 	time_spent = (double)(end - begin1) / CLOCKS_PER_SEC;
// 	printf("File creation time: %d\n",time_spent);
// 	time_spent = (double)(end - begin0) / CLOCKS_PER_SEC;
// 	printf("Total execution time: %d\n",time_spent);
// }