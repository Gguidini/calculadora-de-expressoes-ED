#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "linkedlist.h"

int errorCheck(t_lista* l){			// função faz validacao da expressao pelos parentesis. 1 = erro; 0 = tudo ok.
	t_elemento* it = l->inicio;		// armazena os parentesis de abertura na stack e remove quando encontra um de fechamento
	int i = 0;				
	t_stack* err = newStack(); 
	while(it != NULL){
		if(it->data == '('){
			push(err, it->data);
		}
		if(it->data == ')'){
			if(!isStackEmpty(err)){
				pop(err);
			}
			else{
				printf("Erro. Parentesis sem fechamento no indice %d\n", i);	// tentativa de remover de stack vazia significa erro.
				return 1;
			}
		}

		it = it->prox;
		i++;
	}

	if(isStackEmpty(err))	// se a stack nao estiver vazia neste ponto, significa erro.
	return 0;

	else
	return 1;
}

t_lista* readInput(){
	t_lista* l = newList();
	char ch;
	printf("Please, insert expression.\n");

	while(scanf("%c", &ch), ch != '\n'){
		if(ch != ' ')
			insertFim(l, ch);
	}
	return l;
}

int getB(){		// 0 = continua; 1 = encerra.
	char ch;
	printf("gostaria de entrar com nova expressao? (S/N)\n");
	while(scanf("%c", &ch), ((ch != 'N') && (ch != 'n') && (ch != 'S') && (ch != 's'))){
		printf("Responder S ou N.\n");
	}
	getchar();
	if(ch == 'N' || ch == 'n'){
		return 1;
	}
	else{
		return 0;
	}
}

int main(){
	t_lista* l = readInput();	// stack para armazenar entrada inicial. 
	int b = 0;	// entrar no loop forcado.
	while(b == 0){			// loop permite que input possa ser recolocado, caso haja erro, sem reiniciar o programa.
							// Ou permite calcular mais de uma expressao sem reiniciar o programa.
		b = errorCheck(l);
		if(b == 0){	
			// tudo certo, prosseguir processamento
			printf("processar...\n");

		}
		else{
			printf("expressao apresenta erros.\n");
		}
		b = getB();
		if(b == 1){		
			printf("obrigado por usar a calculadora de expressoes ED\n");
			return 0;
		}
		else{
			l = readInput();		
		}
	}
	
	return 0;
}
