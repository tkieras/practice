/* Checks for balanced parentheses, brackets and braces; does not handle comments or quoted strings */

#include <stdio.h>

#define TRUE 0;
#define FALSE 1;

int main(){
	char stack[100];
	int stack_idx;
	int c, valid;
	char tmp;

	stack_idx = 0;
	valid = TRUE;

	while((c = getchar()) != EOF){
		if(c == '(' || c == '{' || c == '['){
			/* push c to stack */
			stack[stack_idx] = c;
			stack_idx++;
		}
		else if(c == ')' || c == '}' || c == ']'){
			/* pop to tmp */
			stack_idx--;
			tmp = stack[stack_idx];

			if(tmp == '(' && c == ')'){
				valid = TRUE;
			}
			else if(tmp == '{' && c == '}'){
				valid = TRUE;
			}
			else if(tmp == '[' && c == ']'){
				valid = TRUE;
			}
			else{
				valid = FALSE;
			}
		}
	}
	if(stack_idx > 0){
		valid = FALSE;
	}
	printf("%d\n", valid);

	return valid;
}
