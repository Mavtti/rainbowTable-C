#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sizeT 5

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

/*"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"*/
/*char* randomHeadGenerator(int pL){ 
	int i = 0;
	char password[pL];
	printf("-- %c --\n","abcdefghijklmnopqrstuvwxyz0123456789"[random() % 36]);
	printf("trrr\n");
	for(i = 0; i < pL-1; i++){
		strcat(password, "abcdefghijklmnopqrstuvwxyz0123456789"[random() % 36]);
		printf("eee\n");
	}
	return password;
}*/

char* tailGenerator(char* myHead){return "oups";}

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



int main(int argc, char* argv[]){
	printf("Start Program ...\n");
	printf("Creating table of size : %d ...\n",sizeT);
	RainbowTable table = generateTable(4);
	printf("Creation completed ...\n");
	RainbowRow* current = table.rows;
	while(current != NULL){
		printf("%s %s\n",current->head,current->tail);
		current = current->next;
	}
}

/*	public String randomHeadGenerator(int passwordLength) {
		StringBuilder result = new StringBuilder();
		String set = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		for (int i = 0; i < passwordLength; i++) {
			int characterIndex = new SecureRandom().nextInt(set.length());
			result.append(set.charAt(characterIndex));
		}
		return result.toString();
	}*/