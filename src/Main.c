#include <time.h>
#include "RainbowCracker.h"

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

int main(int argc, char* argv[]){
    
    if(argv[1] == "1"){
    	createTable();
    }
    if(argv[1] == "2"){
	if(strlen(argv[2]) != 8){
		printf("Need password of length 8.\n");
		return EXIT_SUCCESS;
	}
	else{ 
		printf("Password to crack: %s .\n", argv[2]);
		RainbowTable* table = findTable("Rainbow.txt");
		printf("Table found.\n");
		printf("--> %s\n",crackHash(table, argv[2]));
	}
	}
    return EXIT_SUCCESS;
