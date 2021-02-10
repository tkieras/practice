#include <stdio.h>

#define IN 1
#define OUT 0

int main(){
	int c, quote, comment;
	quote = OUT;
	comment = OUT;

	while((c = getchar()) != EOF){
		if(c == '"' && quote == OUT){
			quote = IN;
			if(comment == OUT)
				putchar(c);
		}
		else if(c == '"' && quote == IN){
			quote = OUT;
			if(comment == OUT)
				putchar(c);
		}
		else if(c == '/' && quote == OUT){
			c = getchar();
			if(c == '*'){
				comment = IN;
			}
			else{
				putchar('/');
				putchar(c);
			}
		}
		else if(c == '*' && quote == OUT){
			c = getchar();
			if(c == '/'){
				comment = OUT;
			}
			else{
				putchar('*');
				putchar(c);
			}
		}
		else if(comment == OUT)
			putchar(c);
	}
}
