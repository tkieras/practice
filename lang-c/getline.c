#include <stdio.h>

#define MAXLINE 5

int my_getline(char s[], int maxline);

int main(){
	char new_line[MAXLINE];
	int l;

	l = my_getline(new_line, MAXLINE);

	printf("%s\n%d\n", new_line, l);
}

int my_getline(char s[], int maxline){
	int c,i;
	/* Question: why doesn't this function put a \0 char at index maxline+1, when input is maxline length and terminated by \n?*/

	/* Answer: the boolean condition is not evaluated 'all at once'; rather, if the first part fails, the rest (including the call to getchar) never is evaluated.*/
	for(i=0; i<maxline-1 && (c = getchar()) != EOF && c != '\n'; ++i){
		s[i] = c;
		
	}
	
	if(c == 'x'){
		s[i] = 'x';
		++i;
	}

	
	s[i] = '\0';

	
	return i;
}