#include "RainbowTable.h"

// Creates a RainbowTable variable
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
		myHead = randomHeadGenerator(myHead, pL);
		char* myTail = tailGenerator(myHead, pL);
		row->head =  myHead;
		row->tail = myTail;
		row->next = myTable.rows;
		myTable.rows = row;
	}
	return myTable;
}

// Generates a Tail based on the head with nbReduction hash/reduction iterations
char* tailGenerator(char* myHead, int passwordLength){
	char * current = malloc(sizeof(char) * strlen(myHead));
	strcpy(current, myHead);
	for(size_t i = 0; i <= nbReduction; i++){
		current = reduction(hash(current), i, passwordLength);
	}
	return current;
}

// Generates a head based on the charset defined in .h file of length "size"
static char *randomHeadGenerator(char* str, size_t size){
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

// It Reduces a hash
char* reduction(char* hash, int index, int passwordLength) {
	long long int entier = 1;
	for(size_t i = 0; i < strlen(hash); i++) {
		entier *= (int) hash[i];
	}
	entier = (entier + (long long int) index) % ((long long int) pow(36, 8));
	int j = passwordLength - 1;
	char* reduction = malloc(passwordLength * sizeof(char));

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

// Generates a SHA-256 hash of a char* reduction
char* hash(char* reduction) {
	SHA256_CTX ctx;
	char *hash = malloc(SHA256_BLOCK_SIZE);
	sha256_init(&ctx);
	sha256_update(&ctx, reduction ,strlen(reduction));
	sha256_final(&ctx, hash);
	return hash;
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
