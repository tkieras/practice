#include <stdio.h>

#define IN 1
#define OUT 0

int main(){
	int c, char_count, word_count, current_state, previous_state;

	/*while((c = getchar()) != EOF){
		putchar(c);
	}*/
	word_count = 0;
	current_state = IN;
	previous_state = OUT;

	for(char_count = 0; (c = getchar()) != EOF; ++char_count){
		if(c == ' ' || c == '\n' || c == '\t')
			current_state = OUT;
		else
			current_state = IN;

		if(current_state &! previous_state)
			++word_count;

		previous_state = current_state;
	}

	printf("Words: %d\n", word_count);
	
}