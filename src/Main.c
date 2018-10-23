#include <time.h>
#include "RainbowCracker.h"

int main(int argc, char* argv[]){
	clock_t begin0 = clock();
	createTable();
    clock_t end = clock();
	double time_spent = (double)(end - begin0) / CLOCKS_PER_SEC;
	unsigned char mot_de_passe = "test123r";
	RainbowTable* table = findTable("Rainbow1.txt");
	startCrack(table, hash(mot_de_passe));
	printf("Total execution time: %f\n",time_spent);
	return EXIT_SUCCESS;
}

int startCrack(RainbowTable* table, unsigned char* hash) {
    clock_t begin = clock();
	printf("Starting to crack hash\n");
    unsigned char* password = crackHash(table, hash);
    printf("The password found is : %s\n", password);
    double end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Crack hash time: %f\n",time_spent);
	return EXIT_SUCCESS;
}

int createTable() {
    clock_t begin0 = clock();
    printf("Start Program ...\n");
	printf("Creating table of size : %d ...\n",sizeT);
	RainbowTable table = generateTable(8);
	clock_t end = clock();
	double time_spent = (double)(end - begin0) / CLOCKS_PER_SEC;
	printf("Table creation time: %f\n",time_spent);
	printf("Creation completed ...\n");
	clock_t begin1 = clock();
	printf("File creation ...\n");
	createFile(table);
	end = clock();
	time_spent = (double)(end - begin1) / CLOCKS_PER_SEC;
	printf("File creation time: %f\n",time_spent);
	return EXIT_SUCCESS;
}