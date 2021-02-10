#include <stdio.h>
#include <stdlib.h>

int main(){
	void* test_ptr = malloc(sizeof(int));

	*(int*)test_ptr = 65;

	printf("%d\n", *(int*)test_ptr);	
	printf("%c\n", *(char*)test_ptr);	
	printf("%f\n", *(float*)test_ptr);	


	return 0;
}