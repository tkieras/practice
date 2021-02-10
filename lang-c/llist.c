#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct LLNode{
	struct LLNode* prev;
	struct LLNode* next;
	void* data;	
};

struct LList{
	struct LLNode* head;
	int size;
};

struct LLNode* init_new_node(void* data){
	struct LLNode* new_node = malloc(sizeof(struct LLNode));
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->data = data;

	return new_node;
}

struct LList init_new_list(void){
	struct LList new_list;
	new_list.head = NULL;
	new_list.size = 0;

	return new_list;
}

void push_to_head(struct LList* list, void* new_data){
		struct LLNode* new_node = init_new_node(new_data);

		if(list->head == NULL){
			list->head = new_node;
		}
		else{
			new_node->next = list->head;
			list->head->prev = new_node;
			list->head = new_node;
		}
		list->size++;

	}	

void* pop_from_head(struct LList* list){
	void* temp;
	struct LLNode* next;

	if(list->head == NULL){
		return 0;
	}
	else{
		temp = (list->head)->data;
		next = list->head->next;
		free(list->head);
		list->head = next;
		list->size--;
		if(list->head != NULL)
			list->head->prev = NULL;
		
	}
	return temp;
}
void clear(struct LList* list){
	while(list->size > 0){
		pop_from_head(list);
	}
}

void insert_at(struct LList* list, struct LLNode* insert_after, void* new_data){

	if(insert_after == NULL){
		return;
	}

	struct LLNode* old_next = insert_after->next;

	struct LLNode* new_node = init_new_node(new_data);

	if(list->head == NULL){
		list->head = new_node;
	}
	else{
		insert_after->next = new_node;
		new_node->next = old_next;
	}
}
int main(){
	int c;
	int* i_ptr;
	struct LList new_list = init_new_list();
	

	while((c = getchar()) != EOF && isdigit(c)){
		i_ptr = malloc(sizeof(int));
		*i_ptr = c - '0';
		push_to_head(&new_list, (void*)i_ptr);
	}

	printf("Size of List: %d\n", new_list.size);
	puts("List Contents:");

	struct LLNode* node_ptr = new_list.head;

	while(node_ptr != NULL){
		printf("%d\n", *(int*)node_ptr->data);
		node_ptr = node_ptr->next;
	}

	i_ptr = (int*)pop_from_head(&new_list);

	printf("Removed: %d\nNew Size: %d\n", *i_ptr, new_list.size);

	node_ptr = new_list.head;

	/* Caller must free memory allocated for data; list only handles the pointers and its own memory */
	while(node_ptr != NULL){
		free(node_ptr->data);
		node_ptr->data = NULL;
		node_ptr = node_ptr->next;
	}

	clear(&new_list);
	printf("Size of List: %d\n", new_list.size);

	return 0;
}

