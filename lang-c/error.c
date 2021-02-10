#include <stdio.h>

void error(char* message){
	printf("%s\n", message);
}

int main(){
	error("Test");
}