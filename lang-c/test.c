#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 50

struct LL_Node { 
    struct LL_Node* prev;      /* pointer to the previous node */
	struct LL_Node* next;		/* pointer to the next node */
	void* data_ptr; 			/* uncommitted pointer to the data item */
	
};

struct Unordered_container {
	struct LL_Node* first;
	struct LL_Node* last;
	int size;
};

struct Person {
	char last_name[NAME_SIZE];
};

int main(){
	struct Person* new_person = malloc(sizeof(struct Person));
	strncpy(new_person->last_name, "Philips", NAME_SIZE);
	
	printf("%s\n", new_person->last_name);

	struct LLNode* new_node = malloc(sizeof(struct LL_Node));
	

/*	printf("%s\n", new_node->new_person->last_name);
*/	free(new_person);
	free(new_node);

	return 0;
}