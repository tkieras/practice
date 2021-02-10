#include <stdio.h>

#define TRUE 1
#define FALSE 0



void strshrnk(char s1[], char s2[]){
	/*removes all instances of any characters in s2 from s1*/
	/* case sensitive */
	/* goal: O(n) */

	int ctable[127]; /* ready for all of ASCII */

	int i;
	char* s_ptr;

	for(i=0; i<127; ++i){
		ctable[i] = FALSE;
	}

	/* populate chartable */
	s_ptr = s2;
	while(*s_ptr != '\0'){
		ctable[*s_ptr] = TRUE;
		s_ptr++;
	}

	/* remove from s1 if in chartable*/
	s_ptr = s1;

	while(*s_ptr != '\0'){
		if(ctable[*_ptr] == TRUE)
	}





}

int main(){

	char* test = "This is a test.";
	char* test2 = "Another test.";

	strshrnk(test, test2);


}