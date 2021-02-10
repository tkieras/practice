
#include <stdio.h>
#include <stdlib.h>

int main(){
	int* x = malloc(sizeof(int)*10);
	char* s = malloc(sizeof(char)*15);

	size_t i = 15;
	getline(&s, &i, stdin);

	for(int i=0; i<10; ++i){
		x[i] = 1+i;
	} 

	for(int i=0; i<10; ++i){
		printf("%d ", x[i]);
	}
	puts("");
	printf("%s\n", s);

	free(x);

}