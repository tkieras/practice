#include <stdio.h>
#include <stdlib.h>

int main(){
	char* test = malloc(sizeof(char)*100);

	/* initialization of test */

	char* ptr_1 = test;
	char* ptr_2 = ptr_1;
	ptr_2++;


	printf("%s\n", test);

	*ptr_1 = *ptr_2;


/*
	while(test[i] != '\0'){
		printf("%d\n", i);
		putchar(test[i]);
		putchar(test[i+1]);
		test[i] = test[j];
		i++;
		j++;
	}*/
	printf("%s\n", test);

	free(test);
	
}