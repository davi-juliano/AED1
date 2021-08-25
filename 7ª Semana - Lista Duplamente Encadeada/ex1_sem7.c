#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

typedef struct lista2 { //Estrutura tipo lista duplamente encadeada
  char info;
  struct lista2* ant;
  struct lista2* prox;
}TLista2;
typedef TLista2 *PLista2;

PLista2 inicia_lista(PLista2 lista){ //Função que inicializa a lista
    return NULL;
}

PLista2 insere_fim (PLista2 l, char v) { //Função que insere no final da lista
  PLista2 novo; 
  PLista2 aux;
  novo = (PLista2) malloc(sizeof(TLista2));

  if (novo == NULL){ //Caso não tenha alocado a memória
    printf("Não foi possivel alocar!");
    return NULL;
  }
  
  novo->info = v;
  novo->prox = NULL;
  
  if (l == NULL) { //Caso seja o primeiro elemento da fila
    novo->ant = NULL;
    l = novo;
    return novo;
  }
  
  else { //Caso já haja elementos na fila
    aux = l;
    while(aux->prox != NULL){
      aux = aux->prox;
    }
    aux->prox = novo;
    novo->ant = aux;
  }
  return l;
}

PLista2 busca_no(PLista2 l, char v){ //Função que busca um nó na lista
  PLista2 p;
  
  for (p=l; p!=NULL; p=p->prox)
    if (p->info == v){
      return p;
    }
    
return NULL; //Retorna NULL caso não haja o nó na lista
}

void imprime_lista(PLista2 lista, char palavra_pos[]){  //Função que coloca os elementos da fila em um vetor de caracteres
  PLista2 p = lista;
  int i=0;
    do {
      palavra_pos[i]=p->info;
      p = p->prox;
      i++;
    }while (p != NULL);
  }

void trocaLetras(PLista2 lista1, PLista2 lista2){ //Função que troca os nós de lugar dentro da fila duplamente encadeada
    PLista2 aux[3];

    if (lista1 == lista2){ //Se essas posições da lista forem iguais, retorna normal
    return;
    }
    
    aux[0] = lista1->ant;
    aux[1] = lista2->ant;
    aux[2] = lista1->prox;
    aux[3] = lista2->prox;

    if ((lista1->prox==lista2 && lista2->ant==lista1) || (lista1->ant==lista2 && lista2->prox==lista1)){ 
        lista1->ant = aux[2];
        lista2->ant = aux[0];
        lista1->prox = aux[3];
        lista2->prox = aux[1];
    } //Caso as listas sejam vizinhas, entra nessa condição
    else {
        lista1->ant = aux[1];
        lista2->ant = aux[0];
        lista1->prox = aux[3];
        lista2->prox = aux[2];
    }//Caso não sejam, entra nessa condição

    if (lista1->ant != NULL) //Verificação se não estão nas pontas
        lista1->ant->prox = lista1;

    if (lista1->prox != NULL)
        lista1->prox->ant = lista1;


    if (lista2->ant != NULL)
        lista2->ant->prox = lista2;

    if (lista2->prox != NULL)
        lista2->prox->ant = lista2;

	return;
}

int main(){
    PLista2 lista, laux1, laux2;
    char palavra_ant[MAX], palavra_pos[MAX], letra1, letra2;
    int i=0;

    lista = inicia_lista(lista);
    laux1 = inicia_lista(laux1);
    laux2 = inicia_lista(laux2);
    
    scanf("%s", &palavra_ant);
    
    while(palavra_ant[i]!=','){ //Inserção da palavra na lista, respeitando o critério de parada ','
        lista = insere_fim(lista, palavra_ant[i]);
        i++;
    }
    
    letra1 = palavra_ant[i+1]; //A letra da palavra sempre vai ser o i+1 e o i+3 (visto que ',' é char)
    letra2 = palavra_ant[i+3];
    
    laux1 = busca_no(lista, letra1); //Busca os nós com as letras digitadas
    laux2 = busca_no(lista, letra2);
    
    trocaLetras(laux1, laux2); //Invocação da função trocaLetras
    
    imprime_lista(lista, palavra_pos); //Inscrição da palavra após a troca 
    
    for(i=0;i<strlen(palavra_pos);i++){ //Impressão da palavra após a troca
        printf("%c",palavra_pos[i]);
    }
}