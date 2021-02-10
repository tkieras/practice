#include <stdio.h>

#define MAXLENGTH 1000

void swap_int(int* a, int* b){
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int reverse_array(int array[], int logical_size){
	int i;
	
	for(i=0; i<(logical_size/2); ++i){	
		swap_int(&array[i], &array[logical_size-1-i]);	
	}

	return 0;
}

int main(){

	int test_array[MAXLENGTH];
	int i, n, j;

	for(i=0; i<MAXLENGTH-1 && (n = getchar()) != EOF && n >= '0' && n <= '9'; ++i){
		test_array[i] = n-'0';
	}

	printf("test_array has %d elements\n", i);

	for(j=0; j<i; ++j){
		printf("%d ", test_array[j]);
	}
	puts("");
	puts("Reversing Array");

	reverse_array(test_array, i);

	for(j=0; j<i; ++j){
		printf("%d ", test_array[j]);
	}
	puts("");

	return 0;
}