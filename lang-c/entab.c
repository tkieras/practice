#include <stdio.h>

#define TABSIZE 10

int main(){
	int c,i,spaces,tabs;

	spaces = tabs = 0;
	while((c = getchar()) != EOF){
		if(c == ' '){
			/* store in buffer */
			/* "Tricky Business" */
			++spaces;
		}
		else{
			/* unload buffer when encounter a non-space character */
			tabs = spaces/TABSIZE;
			spaces = spaces%TABSIZE;

			for(i=0; i<tabs; ++i)
				putchar('\t');
			for(i=0; i<spaces; ++i)
				putchar(' ');

			spaces = tabs = 0;

			putchar(c);
		}
	}

	return 0;
}
