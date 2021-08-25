#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINHA 100

typedef struct no *pme;  
struct no { //Estrutura da linha da matriz
  int col;
  char genero;
  pme prox;
};
typedef pme matriz[MAX_LINHA];  //Definição da estrutura da matriz

void inicializa(matriz m, int l){ //Inicialização da matriz
  int i;
  for (i=0; i<l; i++){
    m[i] = NULL;
  }
}

void insere(matriz m, int i,int j, char genero){ //Função de inserção da matriz
  pme novo, p;
  int aux1;
  char aux2;
  novo = (pme)malloc(sizeof(struct no));
  novo->genero = genero;
  novo->col = j;
  novo->prox = NULL;
  if (m[i]==NULL){
    m[i] = novo;
  }
  else {
    for(p = m[i]; p->prox!=NULL; p=p->prox);
      p->prox = novo;
  }

  for(p = m[i]; p->prox!=NULL; p=p->prox){ //Ordena a linha da matriz em ordem crescente
	if(p->col > p->prox->col){
		aux1 = p->col;
		aux2 = p->genero;
		p->col = p->prox->col;
		p->genero = p->prox->genero;
		p->prox->col = aux1;
		p->prox->genero = aux2;
	}
  }
}

void imprime_matriz_inteira(matriz m, int tlin, int tcol ){ //Função que imprime a matriz inteira
  pme p;
  int i,j;

    printf("\nMatriz Inteira:\n");
  for(i=0;i<tlin;i++){
    p = m[i];
    for(j=0;j<tcol;j++){
      if ((p!=NULL) && (p->col==j)){
        printf(" 1 ");
        p = p->prox;
      }
      else{
        printf(" 0 ");
      }
    }
  printf("\n");
  }
}

void imprime_matriz_condensada(matriz m, int tlin, int tcol ){ //Função que imprime a matriz condensada
  pme p;
  int i,j;

    printf("\nMatriz Condensada:\n");
  for(i=0;i<tlin;i++){
    printf("Cliente %d\nFilmes assistidos (filme e genero):\n", i+1);
    p = m[i];
    for(j=0;j<tcol;j++){
      if ((p!=NULL) && (p->col==j)){
        printf("%d  %c\n", (p->col)+1, p->genero);
        p = p->prox;
      }
    }
  printf("\n");
  }
}

void mais_visto(matriz m, int tlin, int tcol){ //Função que verifica o gênero mais visto
	int i,j, conta[8];
	pme p;
	
	for(i=0;i<8;i++){ //Inicialização do vetor que conta quantidade de cada gênero
	    conta[i] = 0;
	}

	for(i=0;i<tlin;i++){  //Contador da quantidade de gêneros assistidos
	    for(p = m[i];p!=NULL;p = p->prox){
	        switch(p->genero){
                case 'A':
                    conta[0] += 1;
        
                case 'R':
                    conta[1] += 1;
        
                case 'S':
                    conta[2] += 1;
        
                case 'C':
                    conta[3] += 1;
        
                case 'M':
                    conta[4] += 1;
        
                case 'D':
                    conta[5] += 1;
        
                case 'F':
                    conta[6] += 1;
        
                case 'P':
                    conta[7] += 1;
	    
	        }
	    }
	}
	
	j = 0;
    
    for(i=1;i<8;i++){ //Comparação dois a dois para o maior
	    if (conta[j]<conta[i])
	        j = i;   
    }    
	
	switch(j){
        case 0 :
            printf("O genero de filme mais assistido foi: Ação");
        break;
        
        case 1 :
           printf("O genero de filme mais assistido foi: Romance");
        break;
        
        case 2 :
            printf("O genero de filme mais assistido foi: Suspense");
        break;
        
        case 3 :
            printf("O genero de filme mais assistido foi: Comédia");
        break;
        
        case 4 :
            printf("O genero de filme mais assistido foi: Musical");
        break;
        
        case 5 :
            printf("O genero de filme mais assistido foi: Drama");
        break;
        
        case 6 :
           printf("O genero de filme mais assistido foi: Ficção");
        break;
        
        case 7 :
            printf("O genero de filme mais assistido foi: Policial");
	    break;
	}
	    
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

int compara_char(char genfilm){ //Função que compara os caracteres para a validação de cada gênero
    
    switch(genfilm){
        case 'A':
            return 1;
        
        case 'R':
            return 1;
        
        case 'S':
            return 1;
        
        case 'C':
            return 1;
        
        case 'M':
            return 1;
        
        case 'D':
            return 1;
        
        case 'F':
            return 1;
        
        case 'P':
            return 1;
        
        default:
            return 0;
    }
    
}


int main( ) {
  matriz m;
  int lin, col, i, j, val, quantfilm, filmeassist,k=1, l=1;
  char genfilm;
  
    printf("Insira a quantidade de filmes disponiveis no catalogo: ");
    scanf("%d", &col);
    
  do{
    printf("Insira a quantidade de clientes do servico: ");
    scanf("%d", &lin);
  }while (lin<0 || lin>= MAX_LINHA);

  inicializa(m,lin); //Inicialização da matriz com o número de linhas
  
  for(i=0; i<lin; i++){
    printf("Quantos filmes o cliente %d ja assistiu? ", k);
    scanf("%d",  &quantfilm);
    while(quantfilm>col){ //Caso exceda o número de um filme, ele continua perguntando quantos filmes foram assistidos
		printf("Número excede o catalogo\nDigite novamente o numero de filmes assistidos pelo cliente %d: ",i+1);
		scanf("%d",&quantfilm);
	}
    l=1;
        for(j=0; j<col; j++){
            while(quantfilm != 0){ //Critério de quantos filmes foram assistidos por uma pessoa
            printf("Digite o numero do %do. filme assistido: ", l);
            scanf("%d", &filmeassist);
            while(filmeassist<0 || filmeassist>col){ //Caso não esteja no intervalo pedido, então ele continua pedindo
                printf("Filme invalido\nInsira o valor correto\nDigite o numero do %do. filme assistido: ", l);
                scanf("%d", &filmeassist);
            }
            l++;
            printf("Digite o genero do filme: ");
            getchar();
            scanf("%c", &genfilm);
            while(compara_char(genfilm) == 0){ //Caso o char não seja um dos gêneros dados, então ele continua perguntando
                printf("Genero invalido!!\nDigite o genero do filme: ");
                getchar();
                scanf("%c", &genfilm);
            }
            insere(m,i,filmeassist-1,genfilm); //Insere os valores passados na matriz
            quantfilm--;
        }

    }
    k++;
  }  
  imprime_matriz_inteira(m,lin,col); //Invocação da matriz inteira
  
  imprime_matriz_condensada(m,lin,col); //Invocação da matriz condensada
  
  mais_visto(m,lin,col); //Mostra o gênero mais visto
  
  libera(m,lin); //Libera a matriz após a utilização da mesma no programa
  
  return(0); 
}