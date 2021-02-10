#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


int main(){
	int i;

	while((i = getchar()) != EOF && isdigit(i)){
		putchar(i);
	}

	return 0;
}