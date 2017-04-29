// biblioteca local para uso de lista simplesmente encadeada.
// alterar struct e functions para conter aquilo que voce precisa.

#include <stdio.h>
#include <stdlib.h>

//typedef struct elemento{									// as declarações de elemento e lista estão comentadas porque
//	char data;		
// int prioridade										// estao no arquivo stack.h ... estava dando erro de compilação.
//	struct elemento* prox;
//} t_elemento;

//typedef struct lista{
//	t_elemento* inicio;
//	t_elemento* fim;
//	int size;
//} t_lista;

t_lista* newList(){											// cria nova lista e retorna o ponteiro para ela
	t_lista* l = (t_lista*) malloc(sizeof(t_lista));		// lista é criada vazia
	l->inicio = NULL;
	l->fim = NULL;
	l->size = 0;
	
	return l;
}

void insertInicio(t_lista* l, char data){						// insere um elemento no inicio da lista. O(1).
	t_elemento* n = (t_elemento*) malloc(sizeof(t_elemento));	// atualiza os ponteiros da lista.
	n->data = data;

	// acertando a prioridade: operandos = 1000, + - = 0, * / = 1, () = 3. caracteres invalidos = 5.
	if(isdigit(data)){
		n->prioridade = 1000;
	}
	else if((data == '+') || (data == '-')){	// parentesis tem uma prioridade menor no codigo para nao serem removidos da stack de operadores
		n->prioridade = 1;						// pelos operadores que vao entre eles.
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

void printList(t_lista* l){				// mostra na tela os conteúdos da lista toda. O(n).
	if(l->inicio == NULL){				// se a lista estiver vazia ele indica lista vazia.
		printf("lista vazia\n");
		return;
	} 		
	t_elemento* curr = l->inicio;
	while(curr != NULL){
		printf("%c", curr->data);
		curr = curr->prox;
	}
	printf("\n");
}
void insertFim(t_lista* l, char data){							// insere um elemento no final da lista. O(1).
	t_elemento* e = (t_elemento*) malloc(sizeof(t_elemento));	// atualiza os ponteiros da lista.
	e->data = data;

	// acertando a prioridade: operandos = 1000, + - = 0, * / = 1, () = 3. caracteres invalidos = 5.
	if(isdigit(data)){
		e->prioridade = 1000;
	}
	else if((data == '+') || (data == '-')){		// parentesis tem uma prioridade menor no codigo para nao serem removidos da stack de operadores
		e->prioridade = 1;							// pelos operadores que vao entre eles.
	}
	else if((data == '*') || (data == '/')){
		e->prioridade = 2;
	}
	else if((data == '(') || (data == ')')){
		e->prioridade = 0;
	}
	else{						// default para caracteres invalidos.
		e->prioridade = 5;
	}

	e->prox = NULL;
	if(l->fim != NULL)
		l->fim->prox = e;
	if(l->inicio == NULL)
		l->inicio = e;
	l->fim = e;
	l->size += 1;
}

void insertPos(t_lista* l, char data, int pos){		// insere elemento em qualquer posiçao da lista. Pior caso O(n).
	if(pos <= 0){									// posições negativas resultam em inserção no início.
		insertInicio(l, data);						// posições maiores do que o tamanho da lista resultam em inserção no final.
		return;
	}
	t_elemento* curr = l->inicio;
	int i;
	
	for(i = 0; (i < pos-1 && curr != NULL); i++){
		curr = curr->prox;
	}
	if(curr == NULL){
		insertFim(l, data);
		return;
	}
	t_elemento* f = (t_elemento*) malloc(sizeof(t_elemento));
	f->data = data;
	f->prox = curr->prox;
	curr->prox = f;
	if(f->prox == NULL){
		l->fim = f;
	}
	l->size += 1;
}

char removeInicio(t_lista* l){			// remove inicio elemento de uma lista. O(1).
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

char removeFim(t_lista* l){				// remove elemento do final da lista. O(n).
	if(l->fim == NULL){ return -1;}		// atualiza os ponteiros da lista.
	else{								// retorna o valor que foi removido da lista.
	char tmp = l->fim->data;
	t_elemento* fim = l->inicio;
	t_elemento* penfim = NULL;
	while(fim->prox != NULL){
		penfim = fim;
		fim = fim->prox;
	}
	
	if(penfim != NULL){
		penfim->prox = NULL;
		l->fim = penfim;
	}
	else{
		l->inicio = NULL;
		l->fim = NULL;
	}
	
	free(fim);
	l->size -= 1;
	return tmp;
	}
}

t_elemento* busca(t_lista* l, int pos){				// retorna o elemento de uma posicao da lista. O(n).
	if(l->inicio == NULL){return NULL;}				// e coloca esse elemento no inicio da lista.
	t_elemento* curr = l->inicio;
	t_elemento* prev = NULL;
	int i;
	for(i = 0; i < pos && curr != NULL; i++){
		prev = curr;
		curr = curr->prox;
	}
	if(curr == NULL){return NULL;}
	if(prev != NULL){
		prev->prox = curr->prox;
		curr->prox = l->inicio;
		l->inicio = curr;
	}
	if(curr == l->fim){
		l->fim = prev;
	}
	return curr;
	
}

int listSize(t_lista* l){	// retorna o tamanho da lista. O(1).
	return l->size;
}

void clearList(t_lista* l){					// remove todos os elementos de uma lista deixando tamanho 0. O(n).
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

void reverse(t_lista* l){
  if(l->inicio == NULL) return;	
  if(l->inicio->prox == NULL) return; 	
    
  if(l->inicio->prox == l->fim){
    l->fim->prox = l->inicio;
    l->inicio->prox = NULL;
    l->inicio = l->fim;
    l->fim = l->fim->prox;
    return;
  }
  
  t_elemento* av = l->inicio->prox->prox;
  
  t_elemento* mid = l->inicio->prox;
  
  t_elemento* back = l->inicio;
  
  back-> prox = NULL;
  l->fim = back;
  while(av != NULL){
    mid->prox = back;
    back = mid;
    mid = av;
    av = av->prox;
  }
  mid->prox = back;
  l->inicio = mid;
}

void deleteList(t_lista* l){			// deleta a lista e todos os elementos que ela contem. O(n).
	clearList(l);
	free(l);
}

int isListEmpty(t_lista* l){		// verifica se a lista esta vazia. O(1).
	if(l->inicio == NULL)			// retorna 1 se estiver vazia e 0 se nao estiver vazia.
		return 1;
	else
		return 0;
}