#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PILHA{ //Estrutura da pilha
    char operador;
    int prioridade_sinal;
    int topo;
    int elemento[20];
    struct PILHA *raiz;
}pilha;

pilha * inicia(pilha *p){ //Iniciador da pilha
	p = (pilha*)malloc(sizeof(pilha));
		p->prioridade_sinal = -1;
		p->topo = -1;
		p->raiz = NULL;
			return p;
}

pilha * insere_pilha(pilha *p, char sinal[],int i, int grau){ //Inserir um elemento de um vetor em uma pilha
    pilha *aux;
	aux = (pilha*)malloc(sizeof(pilha));
	aux->raiz = p;
	aux->operador = sinal[i];
	aux->prioridade_sinal = grau;
	(aux->topo)++;
	    return aux;
    	
}

void empilhar(pilha *p, int num) { //Empilhar um valor no vetor da pilha
    ++(p->topo);
    p->elemento[p->topo] = num;
    //printf("e");
    return;
}

int desempilhar(pilha *p) {  //Desempilhar da pilha um elemento apenas
    --(p->topo);
    //printf("d");
    return p->elemento[p->topo + 1];
}

int transformaint(char a){  //Função que transforma char em int
    int j = a - '0';
    //printf("\nval%d",j);
    return j;
}

pilha * remove_pilha(pilha *p,int grau, int j, char posfix[]){ //Remover da pilha e colocando no vetor posfixo
	pilha *aux;
	while(grau <= p->prioridade_sinal){
		printf("%c",p->operador); //Printando na tela os operadores que estão em maior prioridade
		posfix[j] = p->operador;
		p = p->raiz;
	}
	aux = p;
		return aux;
}

char funcaoprincipal(char infix[], int tam_expressao, char posfix[]){ //Função transformação
    pilha *p;
    int i=0, grau=0, j=0, k=0, y=0;
    int num1, num2;
        
    p = inicia(p);

	for(i=0;i<=tam_expressao;i++){  //Transformação em Pósfixo
        switch( infix[i] ){

    		case '+':  
	    	case '-': 
		        grau = 1;
			    break;

		    case '*': 
		    case '/': 
		        grau = 2;
			    break;

		    case '^': 
		        grau = 3;
			    break;

		    case '(':
		        grau = 4;
			    break;

		    case ')':
                break;

    	    default:
	            grau = 5;
			    printf("%c",infix[i]);
	            posfix[j]=infix[i]; 
	            j++;
        }
        
        if(grau != 5){
	        if(grau>=p->prioridade_sinal)
	    	    p=insere_pilha(p,infix,i,grau);

    	    else{
	    	    p = remove_pilha(p,grau,j, posfix);
                p = insere_pilha(p,infix,i,grau);
	        }
        }  
    }

	while(p!=NULL){
		printf("%c",p->operador);
		posfix[j]=(char)p->operador;
		p = p->raiz;
		j++;
	}
	
	free(p);
	p=inicia(p);
	i=0;
	
	do{  //Cálculo da expressão em Pósfixo para um valor inteiro
	    if((int)posfix[i] >= 48 && 57 >= (int)posfix[i]){
	        empilhar(p,transformaint(posfix[i]));
	    }
	    else {
            num2 = desempilhar(p); 
            num1 = desempilhar(p); 
            switch (posfix[i]) {
            case '+': 
                empilhar(p, (int)num1+num2); 
                break;
            case '-': 
                empilhar(p, (int)num1-num2);
                break;
            case '*':
                empilhar(p, (int)num1*num2);
                break;
            case '/': 
                empilhar(p, (int)num1/num2); 
                break;
            case '^':
                empilhar(p, (int)num1/num2); 
                break;
                
            }
	    }
	    i++;
	}while(infix[i]!='\0');

    printf("\n%d\n", desempilhar(p));
	free(p);

}

int main(){
    char infix[50], posfix[50] = "";
    pilha *p;
    int i=0, tam_expressao,grau=0;
    
	scanf("%s",&infix);
    funcaoprincipal(infix, strlen(infix), posfix);
    
}