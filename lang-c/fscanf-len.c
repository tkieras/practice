#include <stdio.h>
#include <stdlib.h>

#define MAXINPUTLENGTH 31
#define INPUTFORMAT "%31s"
#define INPUTARRAYSIZE MAXINPUTLENGTH + 1

int main(){
	FILE* newfile;
	char* firstname;
	char* lastname;
	char* phoneno;

	newfile = fopen("test.txt", "r");
	firstname = malloc(sizeof(char)*INPUTARRAYSIZE);
	lastname = malloc(sizeof(char)*INPUTARRAYSIZE);
	phoneno = malloc(sizeof(char)*INPUTARRAYSIZE);

	fscanf(newfile, INPUTFORMAT, firstname);
	fscanf(newfile, INPUTFORMAT, lastname);
	fscanf(newfile, INPUTFORMAT, phoneno);

	printf("%s\n", firstname);
	printf("%s\n", lastname);
	printf("%s\n", phoneno);

	/* behavior as expected: only 31 chars are read, or until first whitespace. 
	If read is terminated by reaching 31 chars, the next read starts at the 32nd char, 
	not after a subsequent whitespace */

	fclose(newfile);
}