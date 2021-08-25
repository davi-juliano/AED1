#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista{  //Estrutura da Lista
    int indice;
    int sumcard;
    struct lista* prox;
}TLista;
typedef TLista* PLista;

void inicia_lista(PLista lista){ //Função que inicia a lista
    lista=NULL;
    return;
}

PLista insere_circular(PLista lista, int valor, int i) { //Função que insere um valor na lista circular
	PLista aux;
	aux = (TLista*) malloc(sizeof(TLista));
	aux->sumcard = valor;
    aux->indice = i;

	if (lista == NULL){ //Caso a lista esteja vazia
	    aux->prox = aux;
	}
	else { //Caso a lista já tenha elementos
		aux->prox = lista->prox;
		lista->prox = aux;
	}
	return aux;
}

PLista remove_valor(PLista lista, int valor){ //Remove um valor da lista
    PLista aux=lista;
    PLista ant=lista;

    if(lista->sumcard == valor){ 
        while(aux->prox!=lista){
            aux=aux->prox;
        }
        aux->prox=lista->prox;
        free(lista);
        aux=aux->prox;
        return aux;
    }

    while(aux->sumcard!=valor){
        if(aux!=lista){
            ant=ant->prox;
        }
        aux=aux->prox;
        
        if(aux==lista){
            return lista;
        }
    }
    ant->prox=aux->prox;
    free(aux);
    return lista;
}

int compara_21(PLista lista){ //Função que compara as somas de cartas e retorna os prints
  PLista p;
  int valor;

  if(lista == NULL){ //Caso a lista seja vazia, ele não entra nas comparações
      return 1;
  }
  
  if (lista !=NULL){ //Caso haja uma lista, ele entra
    p = lista->prox;
    do {
      if(p->sumcard > 21){ //Comparação maior que 21
        printf("O jogador %d ultrapassou 21! Eliminado!\n", (p->indice)+1);
        lista = remove_valor(lista, p->sumcard);
        return 0;
      }
      if(p->sumcard == 21){ //Comparação igual a 21
        printf("Jogador vencedor: %d. Pontuação: %d\n", (p->indice)+1, p->sumcard);
        return 1;
      }
      p = p->prox;
    } while (p != lista->prox); //Vai fazer por toda a lista
  }
}

void imprime_circular(PLista lista){ //Impressão dos valores da lista
  PLista p = lista->prox;
  printf("Situação da Lista:\n");
    do {
      printf("Jogador = %d pontuacao = %d\n", (p->indice)+1, p->sumcard);
      p = p->prox;
    }while (p != lista->prox);
  }

int compara_carta(char c[]){ //Função que entra uma string e sai um valor inteiro
  int valor;
  char carta[2];
  
    if(strcmp(c, "A") == 0){
      valor = 11;
      return valor;
    }
    if(strcmp(c, "K") == 0){
      valor = 10;
      return valor;
    }
    if(strcmp(c, "J") == 0){
      valor = 10;
      return valor;
    }
    if(strcmp(c, "Q") == 0){
      valor = 10;
      return valor;
    }
    if(strcmp(c, "10") == 0){
      valor = 10;
      return valor;
    }
    if(strcmp(c, "9") == 0){
      valor = 9;
      return valor;
    }
    if(strcmp(c, "8") == 0){
      valor = 8;
      return valor;
    }
    if(strcmp(c, "7") == 0){
      valor = 7;
      return valor;
    }
    if(strcmp(c, "6") == 0){
      valor = 6;
      return valor;
    }
    if(strcmp(c, "5") == 0){
      valor = 5;
      return valor;
    }
    if(strcmp(c, "4") == 0){
      valor = 4;
      return valor;
    }
    if(strcmp(c, "3") == 0){
      valor = 3;
      return valor;
    }
    if(strcmp(c, "2") == 0){
      valor = 2;
      return valor;
    }
    else{
    printf("Valor Inválido!! Digite um novo valor:");
    scanf("%s", &carta);
    valor = compara_carta(carta); //Utilização da função dentro da função para caso tenha um valor inválido
    return valor;
    }
}

PLista adiciona_valor(PLista lista, char c[]){ //Função pra adicionar valores à soma das cartas da lista
  lista->sumcard = lista->sumcard + compara_carta(c) ;
  return lista;
}

void libera_lista(PLista lista){ //Função que libera a lista
    PLista p=lista->prox;
    PLista q=lista;
    while(p!=lista){
        q=p;
        p=p->prox;
        free(q);
    }
    free(lista);
}


int main(){
    int valor, jogadores, i;
    PLista lista;
    char c[2];

    inicia_lista(lista);

    printf("Digite a quantidade de jogadores:\n");
    scanf("%d", &jogadores);

    for(i=0;i<jogadores;i++){ //A primeira rodada nunca irá superar o numero 21, então está separado de quando há incremento
      printf("Digite uma carta (numero de 2 a 10 ou as letras A, J, K ou Q):");
        scanf("%s", &c);
      valor = compara_carta(c);

      lista = insere_circular(lista, valor, i);
    }
    
    imprime_circular(lista);
    i=0;
    
    do{ //Incrementos nos jogadores já existentes
      printf("Digite uma carta (numero de 2 a 10 ou as letras A, J, K ou Q):");
      scanf("%s", &c);

      lista=lista->prox;
      lista = adiciona_valor(lista, c);
      i++;
      
      if(i%jogadores == 0){ //Imprime a lista sempre que gera uma rodada
        imprime_circular(lista);
        i=0;
      }
      
    }while(compara_21(lista) != 1);

    libera_lista(lista);
    return 0;

}