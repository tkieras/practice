#include <iostream>

int test_call_by_reference(int& a, int& b){
	int result, i;

	result = i = 0;
	
	while(i < b){
		result = result + a;
		++i;
	}

	return result;
}

int main(){

	int result;
	int a, b;

	a = 5;
	b = 2;

	result = test_call_by_reference(a, b);
	printf("%d\n", result);

	
	return 0;
}