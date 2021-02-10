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
	const int i = 4898888;
	
	int_to_char(i);

	puts("");


	return 0;
}