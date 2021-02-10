#include <stdio.h>

int fn1(int x, int y){
	return x+y;
}
int fn2(int x, int y){
	return x*y;
}
int fn3(int x, int y, int (*fn)(int, int)){
	return (*fn)(x, y);
}

int main(){
	int a, b;
	a = 5;
	b = 10;

	int (*fn_ptr)(int,int);

	fn_ptr = &fn2;

	printf("%d\n", (*fn_ptr)(a,b));

	fn_ptr = &fn1;

	printf("%d\n", (*fn_ptr)(a,b));

	printf("%d\n", fn3(a,b, fn_ptr));

	return 0;
}