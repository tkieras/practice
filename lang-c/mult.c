#include <stdio.h>

/* Implements positive integer multiplication by addition */
int test_call_by_value(int a, int b){
	int result, i;

	result = i = 0;
	
	while(i < b){
		result = result + a;
		++i;
	}

	return result;
}

/*Note, C vs. C++ syntax for call-by-reference; C does this by pointers int* a; fn(&a); C++ has int& a and fn(a) */
int test_call_by_reference(int* a, int* b){
	int result, i;

	result = i = 0;
	
	while(i < *b){
		result = result + *a;
		++i;
	}

	return result;
}


int main(){
	int result;
	int a, b;

	a = 5;
	b = 2;

	result = test_call_by_value(5, 1);
	printf("%d\n", result);

	result = test_call_by_reference(&a, &b);
	printf("%d\n", result);
	
	return 0;
}