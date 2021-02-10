#include <stdio.h>

int main(){
	
	int x, y;
	x = 5;
	y = 10;

	int *a;
	int *b;

	a = &x;
	b = &y;

	*a = 4;
	*b = 9;

	x = 3;
	y = 8;

	*a = *b;
	
	printf("%d %d\n", x, y);
	printf("%d %d\n", *a, *b);

}