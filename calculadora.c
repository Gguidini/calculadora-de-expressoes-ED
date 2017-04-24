#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "linkedlist.h"

int main(){
	char ch;
	t_lista* l = newList();	// stack para armazenar entrada inicial. 
	printf("insert expression.\n");

	while(scanf("%c", &ch), ch != '\n'){
		if(ch != ' ')
			insertFim(l, ch);
	}

	
	return 0;
}
