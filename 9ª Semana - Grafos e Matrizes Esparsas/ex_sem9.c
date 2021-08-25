#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINHA 100

typedef struct no *pme;  
struct no { //Estrutura da linha da matriz
  int col, lin;
  pme prox;
};
typedef pme matriz[MAX_LINHA];  //Definição da estrutura da matriz

void inicializa(matriz m, int l){ //Inicialização da matriz
  int i;
  for (i=0; i<=l; i++){
    m[i] = NULL;
  }
}

void insere(matriz m, int li, int co) {  //Função de inserir um grafo na matriz 
	pme novo, p = m[li];
	int aux;

	novo = (pme)malloc(sizeof(struct no));
	novo->col = co;
	novo->prox = NULL;

	if (m[li]==NULL){
	m[li] = novo;
	return;
	}
	else {
		for(p = m[li]; p->prox!=NULL; p=p->prox);
		    p->prox = novo;
	}
	
	for(p = m[li]; p->prox!=NULL; p=p->prox){  //Ordenação dentro da Insere
		if(novo->col < p->col){
		aux = novo->col;
		novo->col = p->col;
		p->col = aux;
		}

	}
}

void imprime_matriz_adjacencia(matriz m, int tlin, int tcol ){  //Impressão da Matriz de Adjacencia
	int i,j;
	pme p;
	
	printf("\nMatriz de Adjacência:\n");
	
	printf("   ");
	for(i=1;i<=tlin;i++)
	printf(" %d ",i);
	
	printf("\n");

	for(i=1;i<=tlin;i++){
		p = m[i];

		printf(" %d ",i);

		for(j=1;j<=tcol;j++)
		
			if ((p!=NULL) && (p->col==j)){
				printf(" 1 ");
				p = p->prox;
			}
			else
			printf(" 0 ");

			printf("\n");
		}

	printf("\n\n");
}

void adjacente(matriz m, int tlin, int tcol){ //Função que imprime os vértices adjacentes
  pme p;
  int i,j;

    p = m[tlin];
    printf("Os vértices adjacentes do vértice %d são:", tlin);
    for(j=1;j<=tcol;j++){
      if ((p!=NULL) && (p->col==j)){
        printf(" %d", p->col);
        p = p->prox;
      }
    }
  printf("\n");
}



void libera(matriz m, int l){ //Função que libera matriz
  pme p, q;
  int i;
  for(i=0;i<l;i++){
    p = m[i];
    while (p!=NULL){
      q = p;
      p = p->prox;
      free(q);
    }
  }
}

int main( ) {
  int lin, col, vert;
	matriz m;
	char orientacao[3]; 

	printf("Informe número de vértices: ");
	scanf("%d",&vert);

	inicializa(m,vert); //Inicialização da Matriz

  printf("O grafo é orientado? ");
    scanf("%s", orientacao);
    getchar();

	printf("Informe conexões, digite 0 para encerrar\n");

	do{  //Fazer até o usuário escrever 0 nas conexões

	    scanf("%d,%d",&lin,&col);

	    if(lin == 0)
	        break;

	    if(strncmp(orientacao,"sim",3)==0){
		    insere(m, lin, col);
	    }
        
        else{
		    insere(m, lin, col);
		    insere(m, col, lin);
	    }
    }while(lin!=0);

	printf("Informe o vértice que deseja saber os adjacentes:\n");
	scanf("%d",&lin);

  imprime_matriz_adjacencia(m,vert,vert); //Invocação da matriz inteira
  
  adjacente(m,lin,vert); //Invocação da função para o cálculo dos vértices adjacentes

  libera(m,vert); //Libera a matriz após a utilização da mesma no programa
  
  return(0); 
}