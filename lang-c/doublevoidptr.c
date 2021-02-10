#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int tmp;
	int *new_int;
	void **array;
	void **dblv_ptr;

	array = malloc(sizeof(void*)*10);

	puts("Input ten integers:");

	dblv_ptr = array;
	for(int i=0; i<10; ++i){
		new_int = malloc(sizeof(int));
		scanf("%d", new_int);
		*dblv_ptr = (void*)new_int;
		dblv_ptr++;
		/* or */
/*		array[i] = (void*)new_int;
*/	}

	puts("Output by array index: ");

	for(int i=0; i<10; ++i){

		printf("%d ", *(int*)(array[i]));
	}

	puts("");

	puts("Output by pointer: ");

	dblv_ptr = array;

	for(int i=0; i<10; ++i){

		printf("%d ", *(int*)(*dblv_ptr));
		dblv_ptr++;
	}
	
	puts("");
}