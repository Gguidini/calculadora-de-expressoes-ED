#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"
#include "linkedlist.h"

int errorCheck(t_lista* l){			// função faz validacao da expressao pelos parentesis. 1, 2, 3 = erro; 0 = tudo ok.
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
		else if((it->prioridade == 1) || (it->prioridade == 2)){ // operadores seguidos
			if((it->prox->prioridade == 1) || (it->prox->prioridade == 2))
			return 1;
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

 
int strLen(char* ch)	// tamanho do numero
{
    int i;
    int count = 0;
    for(i = 0; ch[i] != '\0' ;i++)
        count++;
    return count;
}
 
long long charToInt (char* ch)	// transforma numero para inteiro
{
    int tam = strLen(ch)-2;
    int i;
    long long int sum = 0;
    for(i = 0 ; ch[i] != '\0' ;i++)
    {
    	if((ch[i] != ' ') && (ch[i] != '@')){
        int dec = (int) pow(10, tam);
        int num = ch[i] - '0' ;
        sum += (num * dec);
        tam -= 1;
    	}
    	else if(ch[i] == '@'){
    		sum *= (-1);
    	}
    }
    return sum;
}
 
int abs(int a){
	return (a >= 0 ? a : (0 - a));
}
int Operacao(t_numStack* jooj, char op, char field)	// executa as operacoes
{	// retorna 0 se sucesso, 1 se fracasso.
	t_numero* sec = numTop(jooj);
	popNum(jooj);
	t_numero* pri = numTop(jooj);
	popNum(jooj);
	
	if((field == 'i') && (op != '/')){
		int b = sec->whole;
		int a = 0;
		if(pri != NULL)
			a = pri->whole;
		
		int c;
		char f = 'i';
		
		
	if(op == '+') c = a + b;
    else if(op == '-') c = a - b;
    else c = a * b;
    
        if(c > 1e9+7)
    {
        printf("---OVERFLOW!---\n");
        return 1;
    }
    
    pushNum(jooj, c, 0, f);
	}
	else{
		if(field == 'i'){
			double b = (double) sec->whole;
			double a = 0;
			
			if(pri != NULL)
			a = (double) pri->whole;
		
		
		char f = 'd';
		double c;
		
		if(b == 0)
        {
            printf("---DIVISAO POR ZERO!---\n");
            return 1;
        }
        c = a / b;
        pushNum(jooj, 0, c, f);
		}
		else{
			double b = sec->frac;
			double a = 0;
			if(pri != NULL){
				a = pri->frac;
			}
			
			char f = 'd';
			double c;
			
			if(op == '+') c = a + b;
    		else if(op == '-') c = a - b;
    		else if(op == '*') c = a * b;
    		else
    {
        if(b == 0)
        {
            printf("---DIVISAO POR ZERO!---\n");
            return 1;
        }
         c = a / b;
         
            if(c > 1e9+7)
    {
        printf("---OVERFLOW!---\n");
        return 1;
    }

    }
    		pushNum(jooj, 0, c, f);
		}
	}
   
    return 0;
}
 
void Resolve(t_lista* l)
{
    t_numStack* jooj = newNumStack();
    t_elemento* curr = l->inicio;
    char num1[11];		// primeiro numero
    int i = 0;
    char prev;
    num1[0] = '\0';
    
    if(curr->data == ' ') curr = curr->prox;
    while(curr)
    {
        if((isdigit(curr->data)) || (curr->data == ' ') || (curr->data == '@'))
        {
            num1[i++] = curr->data;
            
            if(((curr->data == ' ') || (curr->data == '@')) && (isdigit(prev))){
            	num1[i] = '\0';
            	int a = charToInt(num1);
            	pushNum(jooj, a, 0, 'i');
            	i = 0;
            	num1[0] = '\0';
            }
            else if(!isdigit(curr->data)){
            	i = 0;
            }
        }
        else
        {
        		if(isdigit(prev)){
        		num1[i++] = ' ';
        		num1[i] = '\0';
            	int a = charToInt(num1);
            	pushNum(jooj, a, 0, 'i');
            	i = 0;
            	num1[0] = '\0';
        		}	
            char f = numTop(jooj)->field;
            if(Operacao(jooj, curr->data, f)) return;	// se Operacao retornar 1 conte esta com problema
        }
        prev = curr->data;
        curr = curr->prox;
    }
    printf("Resultado = ");
    t_numero* r = numTop(jooj);
    if(r->field == 'd'){
    	printf("%lf", r->frac);
    }
    else{
    	printf("%d", r->whole);
    }
    printf("\n");
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
			
			Resolve(l);
		}
		else{
			if(b == 1)
			printf("expressao apresenta erros.\n");
			
			else if(b == 2)
			printf("expressao sem numeros.\n");
			
			else if(b == 3)
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
