// biblioteca local para uso de stack implementada com lista simplesmente encadeada.
// alterar struct e functions - da bibliotaca linkedlist.h - para conter aquilo que voce precisa.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct elemento{
	char data;
	int prioridade;
	struct elemento* prox;
} t_elemento;

typedef struct lista{
	t_elemento* inicio;
	t_elemento* fim;
	int size;
} t_lista;

typedef struct numero{
	struct numero* prox;
	char field;
	int whole;
	double frac;
} t_numero;

typedef struct numStack{
	t_numero* inicio;
	t_numero* fim;
	int size;
} t_numStack;

typedef t_lista t_stack;

t_stack* newStack(){                // cria uma nova stack
	t_lista* l = (t_lista*) malloc(sizeof(t_lista));		// lista é criada vazia
	l->inicio = NULL;
	l->fim = NULL;
	l->size = 0;
	
	return l;
}

t_numStack* newNumStack(){                // cria uma nova stack de numeros
	t_numStack* l = (t_numStack*) malloc(sizeof(t_numStack));		// lista é criada vazia
	l->inicio = NULL;
	l->fim = NULL;
	l->size = 0;
	
	return l;
}

void push(t_stack* l, char data){     // insere novo elemento no topo da stack. O(1).
    t_elemento* n = (t_elemento*) malloc(sizeof(t_elemento));	// atualiza os ponteiros da lista.
	n->data = data;

	// acertando a prioridade: operandos = 1000, + - = 0, * / = 1, () = 3. caracteres invalidos = 5.
	if(isdigit(data)){
		n->prioridade = 1000;
	}
	else if((data == '+') || (data == '-')){		// parentesis tem uma prioridade menor no codigo para nao serem removidos da stack de operadores
		n->prioridade = 1;							// pelos operadores que vao entre eles.
	}
	else if((data == '*') || (data == '/')){
		n->prioridade = 2;
	}
	else if((data == '(') || (data == ')')){
		n->prioridade = 0;
	}
	else{						// default para caracteres invalidos.
		n->prioridade = 5;
	}
	n->prox = l->inicio;
	l->inicio = n;
	l->size += 1;
	if(l->fim == NULL)
		l->fim = n;
}

void pushNum(t_numStack* s, int inter, double dou, char f){
	t_numero* n = (t_numero*) malloc(sizeof(t_numero));
	n->whole = inter;
	n->frac = dou;
	n->field = f;
	n->prox = s->inicio;
	s->inicio = n;
	s->size += 1;
	if(s->fim == NULL)
		s->fim = n;
}

t_elemento* top(t_stack* stack){            // acessa o topo da stack sem remove-lo. O(1).
    return stack->inicio;    
}

t_numero* numTop(t_numStack* s){
	return s->inicio;
}
char pop(t_stack* l){     // remove o topo da stack. O(1).
    	if(l->inicio == NULL) return 'e';	// faz o handling da memoria para evitar vazamentos.
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

void popNum(t_numStack* s){
	if(s->inicio == NULL) return;
	
	t_numero* r = s->inicio;
	s->inicio = r->prox;
	free(r);
	
	if(s->inicio == NULL)
		s->fim = NULL;
	
	s->size -= 1;
}

int stackSize(t_stack* stack){      // retorna o tamanho da stack.
    return stack->size;
}

int numStackSize(t_numStack* s){
	return s->size;
}

int isStackEmpty(t_stack* s){       // verifica se stack esta vazia. 
 	return (s->size == 0 ? 1 : 0);
}

int isNumStasckEmpty(t_numStack* s){
	return (s->size == 0 ? 1 : 0);
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

void clearNumStack(t_numStack* l){
		if(l->inicio == NULL){					// nao destroi a lista em si, somente os elementos dela.
		return;
	}
	t_numero* curr = l->inicio;
	t_numero* prev = NULL;
	while(curr != NULL){
		prev = curr;
		curr = curr->prox;
		free(prev);
	}
	
	l->inicio = NULL;
	l->fim = NULL;
	l->size = 0;
}