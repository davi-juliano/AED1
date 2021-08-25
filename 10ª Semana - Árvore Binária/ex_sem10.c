/* Utilização do arquivo arv.txt dado abaixo:
A 3 B C D
B 2 E F
E 2 K L
F 0
K 0
L 0
C 1 G
G 0
D 3 H I J
H 1 M
M 0
I 0
J 0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arv { //Definindo a estrutura de uma árvore
    char info;
    struct arv* esq;
    struct arv* dir;
}TArv;
typedef TArv *PArv;

void inicializa_arvore(PArv arvore){ //Função que inicializa a árvore
    arvore=NULL;
}

PArv cria(char c, PArv sae, PArv sad) {  //Função que cria uma "raíz" que não existe
    PArv p = (PArv)malloc(sizeof(TArv));
    p->info = c;
    p->esq = sae;
    p->dir = sad;
    return p;
}

PArv insere(char c[], PArv sae, PArv sad,int j, int k){ //Função que cria um nó e insere em uma raíz 
  PArv p;
  int i=j;
    if(k==0)
        return NULL;

    p = (PArv)malloc(sizeof(TArv));
    p->info = c[j];
    p->esq = NULL;
    p->dir = (insere(c,NULL,NULL,++i, --k)); //Ele insere todos os filhos da raíz de maneira recursiva
    return p;
}

void imprimeIn (PArv a){ //Função que imprime em ordem infixa
  if (a!=NULL) {
    imprimeIn(a->esq);
    printf("%c ", a->info);
    imprimeIn(a->dir);
  }
}

void imprimePre (PArv a) { //Função que imprime em ordem pré-fixa
  if (a!=NULL) {
    printf("%c ", a->info);
    imprimePre(a->esq);
    imprimePre(a->dir);
  }
}

PArv busca(PArv p, char dado){ //Função que busca um nó de acordo com o dado dele
    PArv aux;   
    if (p==NULL){
      return NULL;   
    }
    if (p->info == dado){ 
      return p;   
    }
    aux = busca(p->esq, dado);   
    if (aux == NULL)   
        aux = busca(p->dir, dado);   
    return aux;   
}

void imprimefilho(PArv no){ //Função que imprime os filhos de um nó
    PArv aux = no->esq;

	while(aux!= NULL){
		printf("%c",aux->info);
		aux = aux->dir;
	}
}

void imprimeirmao(PArv no){ //Função que imprime os irmãos de um nó
    PArv aux = no->dir;

	while(aux!= NULL){
		printf("%c",aux->info);
		aux = aux->dir;
	}
}

PArv libera (PArv a){  //Função que libera a árvore 
    if (a!=NULL) {
        libera(a->esq);
        libera(a->dir);
        free(a); 
    }
    return NULL;
}

int main(){   
    FILE *arq; 
    char vetor[70], filho[70]; //Declaração das variáveis
    int menu = 0, j=0,i=0,l=0, k=0;
    PArv arvore,arvaux;

    inicializa_arvore(arvore);
    inicializa_arvore(arvaux);
    arq = fopen("arv.txt", "r");
  
while (!feof(arq)){ //Abertura do arquivo para a leitura e a inserção da árvore em paralelo
    fgets(vetor, 100, arq);
    
    while(vetor[i]!='\n'){ //Passa as informações da linha do arquivo para o vetor de filho
        l = i%2;
        if(l==0){
        filho[j]=vetor[i];
        j++;
        }
        i++;
    }
    
    arvaux = busca(arvore, filho[0]); //Procura se na árvore já tem um nó com essa informação
    
    if(arvaux==NULL){ //Se não, cria esse nó.
        arvore = cria(filho[0],NULL,NULL);
        arvaux = arvore;
        k = filho[1]-'0'; //Utilização do numero a frente da informação da raíz como parâmetro de parada
        if(k!=0){
        j=2;
        arvaux->esq = insere(filho,NULL,NULL,j, k);
        }
    }
    else{ //Se sim, adiciona já na árvore
        k=filho[1]-'0'; //Utilização do numero a frente da informação da raíz como parâmetro de parada
        if(k!=0){
        j=2;
        arvaux->esq = insere(filho,NULL,NULL,j,k);
    
        }    
    }
    j=0;
    i=0;
}
  do{ //Menu para visualizar as ordens, filhos e irmãos
    
      printf("Selecione 1 para imprimir a árvore resultante em pré-ordem;\n");    
      printf("Selecione 2 para imprimir a árvore resultante em ordem infixa;\n");
      printf("Selecione 3 para imprimir os filhos de um dado nó\n");
      printf("Selecione 4 para imprimir os irmão de um dado nó\n");
      printf("Selecione 5 para sair\n");
        
      scanf("%d", &menu);
      getchar();
      
      switch(menu){
        case 1: //Impressão da árvore em ordem pré-fixa
          printf("A árvore em pré-ordem é dada por:");
          imprimePre(arvore);
          printf("\n");
          break;

        case 2: //Impressão da árvore em ordem infixa 
          printf("A árvore em ordem infixa é dada por:");
          imprimeIn(arvore);
          printf("\n");
          break;

        case 3: //Impressão dos filhos de um determinado nó
          printf("Qual nó quer encontrar os filhos?\n");
          scanf("%c", &filho[0]);
          getchar();
          if((arvaux = (busca(arvore, filho[0]))) == NULL){
            printf("Não existe esse nó! Digite outro:");
            scanf("%c", &filho[0]);
          }
          printf("Os filhos do nó pedido é:");
          imprimefilho(arvaux);
          printf("\n");
          break;

        case 4: //Impressão dos irmãos de um determinado nó
          printf("Qual nó quer encontrar os irmãos?\n");
          scanf("%c", &filho[0]);
          getchar();
          if((arvaux = (busca(arvore, filho[0]))) == NULL){
            printf("Não existe esse nó! Digite outro:");
            scanf("%c", &filho[0]);
          }
          printf("Os irmãos do nó pedido é:");
          imprimeirmao(arvaux);
          printf("\n");
          break;

        case 5: //Sair do programa e liberar os espaços adquiridos
          printf("Você saiu do programa!");
          libera(arvore);
          break;

        default: 
          printf("Comando Inválido! Selecione um valor válido:");
          scanf("%d", &menu);
          break;
        };

    }while(menu != 5);

    return 0;
}