#include <stdio.h>

void int_to_char(int i){
	if(i<10){
		putchar('0'+i);
	}
	else{
		int_to_char(i/10);
		int_to_char(i%10);
	}
}

int main(){
	int c, n;
	n = 0;

	putchar('0'+n);
	putchar('\t');
	++n;
	while((c = getchar()) != EOF){
		if(c == '\n'){
			putchar('\n');
			int_to_char(n);
			putchar('\t');
			++n;
		}
		else{
			putchar(c);
		}
	}
	putchar('\n');

}