#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"
#include "linkedlist.h"

int errorCheck(t_lista* l){			// função faz validacao da expressao pelos parentesis. 1 = erro; 0 = tudo ok.
	t_elemento* it = l->inicio;		// armazena os parentesis de abertura na stack e remove quando encontra um de fechamento			
	t_stack* err = newStack(); 
	int b = 0;	// flag de numeros
	while(it != NULL){
		if(isdigit(it->data)){
			b = 1;
		}
		
		else if(it->prioridade == 5){	// flag para caracteres invalidos (letras)
			return 3;
		}
		else if(it->data == '('){
			push(err, it->data);
		}
		else if(it->data == ')'){
			if(!isStackEmpty(err)){
				pop(err);
			}
			else{
				// tentativa de remover de stack vazia significa erro.
				return 1;
			}
		}

		it = it->prox;
	}
	if(b == 0){		// significa que nao ha nenhum numero na expressao
		return 2;
	}
	
	if(!isStackEmpty(err))	// se a stack nao estiver vazia neste ponto, significa erro.
	return 1;

	else					// escopos estao ok
	return 0;
}

t_lista* readInput(){			// leitura da expressao e correcao de pequenos erros que possivelmente podem ocorrer no input
	t_lista* l = newList();
	char ch;
	printf("Please, insert expression.\n");

	while(scanf("%c", &ch), ch != '\n'){
		if(ch != ' '){
			if(!isListEmpty(l)){	// evitar seg fault
				if(ch == '('){		// adiciona sinal de * caso a expressao seja, por exemplo, a(b+c).
					if(isdigit(l->fim->data)){
						insertFim(l, '*');
					}
				}
				else if(isdigit(ch)){	// adiciona sinal de * caso a expressao seja do tipo (b+c)a.
					if(l->fim->data == ')'){
						insertFim(l, '*');
					}
				}
			}
			insertFim(l, ch);
		}
	}
	return l;
}

int getB(){		// 0 = continua; 1 = encerra.
	char ch;
	printf("gostaria de entrar com nova expressao? (S/N)\n");
	while(scanf("%c", &ch), ((ch != 'N') && (ch != 'n') && (ch != 'S') && (ch != 's'))){	// while evita erros como inputs de mais de um caractere.
		printf("Responder S ou N.\n");
	}
	getchar();
	if(ch == 'N' || ch == 'n'){		// nao eh case sensitive
		return 1;
	}
	else{
		return 0;
	}
}

t_lista* inToPos(t_lista* l){
	t_stack* aux = newStack();
	t_lista* nova = newList();
	t_elemento* it = l->inicio;
	
	int b = 1; // marcador de numeros
	while(it != NULL){
		if(isdigit(it->data)){
			// digitos sao adicionados diretamente para a saida
			if(b == 0){
				insertFim(nova, ' ');
			}
			b = 1;
			insertFim(nova, it->data);
			
		}
		else{
			b = 0;
				// operandos e parentesis
				if((it->data == '(') || (it->data == ')')){
					if(it->data == '('){
						push(aux, it->data);
					}
					else{
						char ch;
						ch = pop(aux);
						while((ch != '(') && (ch != 'e')){	// garantido que pelo menos havera um ( na stack.
						insertFim(nova, ch);
						ch = pop(aux);
					}
					}
				}
				else{
				if(isStackEmpty(aux)){
					push(aux, it->data);
				}
				else if(top(aux)->prioridade < it->prioridade){
					push(aux, it->data);
				}
				else{
					while((!isStackEmpty(aux)) && (top(aux)->prioridade) >= it->prioridade){
						insertFim(nova, top(aux)->data);
						pop(aux);
					}

					push(aux, it->data);
				}
			}
		}
		it = it->prox;
	}
	while(!isStackEmpty(aux)){
		insertFim(nova, top(aux)->data);
		pop(aux);
	}

	clearList(l);
	return nova;
}

void showHelp(){	// mostra as regras de formatacao e operacoes disponiveis.
	printf("* CALCULADORA DE EXPRESSOES *\n");
	printf("Operaçoes Disponiveis:\n- adicao (+)\n-subtracao (-)\n");
	printf("-multiplicacao (*)\n-divisao (/)\n\n");
	printf("INSIRA SOMENTE NUMEROS E OPERANDOS. INCOGNITAS NAO SAO ACEITAS.\n");

}
int main(){
	showHelp();
	t_lista* l = readInput();	// stack para armazenar entrada inicial. 
	int b = 0;	// entrar no loop forcado.
	while(b == 0){			// loop permite que input possa ser recolocado, caso haja erro, sem reiniciar o programa.
							// Ou permite calcular mais de uma expressao sem reiniciar o programa.
		b = errorCheck(l);
		if(b == 0){	
			// tudo certo, prosseguir processamento
			printf("processar...\n");
			l = inToPos(l);
			printf("posfixa: ");
			printList(l);
		}
		else{
			if(b == 1)
			printf("expressao apresenta erros.\n");
			
			else if(b == 2)
			printf("expressao sem numeros.\n");
			
			else
			printf("expressao apresenta caractere invalido\n");
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
