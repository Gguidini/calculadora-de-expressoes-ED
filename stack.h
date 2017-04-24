// biblioteca local para uso de stack implementada com lista simplesmente encadeada.
// alterar struct e functions - da bibliotaca linkedlist.h - para conter aquilo que voce precisa.

#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
	char data;
	struct elemento* prox;
} t_elemento;

typedef struct lista{
	t_elemento* inicio;
	t_elemento* fim;
	int size;
} t_lista;

typedef t_lista t_stack;

t_stack* newStack(){                // cria uma nova stack
	t_lista* l = (t_lista*) malloc(sizeof(t_lista));		// lista é criada vazia
	l->inicio = NULL;
	l->fim = NULL;
	l->size = 0;
	
	return l;
}


void pushTop(t_stack* l, char data){     // insere novo elemento no toppo da stack. O(1).
    t_elemento* n = (t_elemento*) malloc(sizeof(t_elemento));	// atualiza os ponteiros da lista.
	n->data = data;
	n->prox = l->inicio;
	l->inicio = n;
	l->size += 1;
	if(l->fim == NULL)
		l->fim = n;
}

char top(t_stack* stack){            // acessa o topo da stack sem remove-lo. O(1).
    return stack->inicio->data;    
}

char popTop(t_stack* l){     // remove o topo da stack. O(1).
    	if(l->inicio == NULL) return -1;	// faz o handling da memoria para evitar vazamentos.
										// retorna o valor do elemento que foi deletado.
	char tmp = l->inicio->data;
	t_elemento* t = l->inicio;
	l->inicio = t->prox;
	free(t);
	if(l->inicio == NULL)
		l->fim = NULL;
	
	l->size -= 1;
	return tmp;
}

int stackSize(t_stack* stack){      // retorna o tamanho da stack.
    return stack->size;
}

int isStackEmpty(t_stack* s){       // verifica se stack esta vazia. 
 	if(s->inicio == NULL)			// retorna 1 se estiver vazia e 0 se nao estiver vazia.
		return 1;
	else
		return 0;
}

void clearStack(t_stack* l){        // limpa a stack, deletando todos os elementos e voltando o tamamnho para 0.
   	if(l->inicio == NULL){					// nao destroi a lista em si, somente os elementos dela.
		return;
	}
	t_elemento* curr = l->inicio;
	t_elemento* prev = NULL;
	while(curr != NULL){
		prev = curr;
		curr = curr->prox;
		free(prev);
	}
	
	l->inicio = NULL;
	l->fim = NULL;
	l->size = 0;
}
