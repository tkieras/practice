#include <stdio.h>

#define IN 1
#define OUT 0

int main(){
	int c, wc, cc, prior_state, current_state, i, j;
	char words[50][50];

	c = wc = cc = prior_state = current_state = 0;

	while((c = getchar()) != EOF){
		if(c == ' ' || c == '\n' || c == '\t')
			current_state = OUT;
		else{
			current_state = IN;
		}


		if(current_state &! prior_state){
			++wc;
		}
		if(current_state){
			++cc;
			words[wc-1][cc-1] = c;
		}
		
		if(prior_state &! current_state){	
			words[wc][cc+1] = '\0';
			cc = 0;
		}

		prior_state = current_state;
	}

	printf("Words: %d\n", wc);

	for(i = 0; i < wc; ++i){
		j = 0;
		while(words[i][j] != '\0'){
			printf("-");
			++j;
		}
		printf("\n");
	}

}