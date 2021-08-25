#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct lista {  //Estrutura da Lista
  float preco;
  int codigo;
  char nome[MAX];
  struct lista* prox;
}TLista;
typedef TLista *PLista;

void inicializa_lista(PLista l){ //Inicializa a Lista usando alocação dinâmica
  l = (TLista*) malloc(sizeof(TLista));
  l = NULL;
  return;
}

PLista inserir_lista(PLista l, int codigo, float preco, char nome[]){ //Função que insere valores na lista
  PLista novo;
  PLista ant = NULL;
  PLista ptaux = l; 

  novo = (TLista*) malloc(sizeof(TLista)); //Faz alocação da estrutura que será o ponteiro da anterior

  novo->codigo = codigo;
  novo->preco = preco;
  strcpy(novo->nome, nome);

  while ((ptaux!=NULL) && (ptaux->codigo)<codigo){
    ant = ptaux;
    ptaux = ptaux->prox;
  }

  if (ant == NULL){
    novo->prox = l;
    l = novo;
  }

  else{
    novo->prox = ant->prox;
    ant->prox = novo;
  }
  return l; //Retorna uma nova lista com o valor inserido numa ordem crescente

}

PLista exclui_produto(PLista l, char nome[]){ //Função que exclui produtos usando o nome do produto
  PLista ant = NULL; 
  PLista p; 
  
  for (p=l;p!=NULL && strcmp(p->nome,nome) == 0; p = p->prox){
    ant = p;
  }

  if (p == NULL){ //Caso para quando não existe o nome inserido na lista
    printf("Não existe esse produto na lista!");
    return l;
  }
  
  if (ant == NULL){
    l = p->prox;
  }

  else{
    ant->prox = p->prox;
  }

//free(p);
printf("O produto %s foi excluído da lista com sucesso!", nome);
return l; //Retorna a nova lista com o valor excluído
}

void busca_produto(PLista l, int codigo){ //Função que busca produtos pelo código dado dentro da lista já criada 
  PLista p=l; 

  while(p->codigo != codigo){ 
    p = p->prox;
  }
  
  if(p==NULL){
    printf("Produto não encontrado!"); //Caso que o código não é encontrado, ele retorna que não encontrou
  }
  else{
    printf("O preço do produto de código %d é %.2f\n", p->codigo, p->preco); //Se encontrou, então ele retorna o código e o preço
  }
  
  free(p);
}

void destroi_lista(PLista l){ //Função que libera toda a lista da alocação
  PLista p = l, t;

  while (p != NULL){
    t = p->prox;
    free(p);
    p = t;
  }
}

int main(void) {
  PLista l;
  int produtos, i, codigo;
  float preco;
  char nome[MAX];

  inicializa_lista(l); //Inicializar a lista

  printf("Quantos produtos quer adicionar na lista?\n"); //Quantos produtos serão adicionados
  scanf("%d", &produtos);

  for(i=0; i<produtos; i++){ 
    printf("Digite o nome do produto %d:", i+1);
    getchar();
    fgets(nome, MAX ,stdin);
    
    printf("Digite o código do produto %d:", i+1);
    scanf("%d", &codigo);
    
    printf("Digite o preço do produto %d:", i+1);
    scanf("%f", &preco);
   
    l = inserir_lista(l, codigo, preco, nome); //Chamada da inserção da nova lista que adicionará os valores dados
  }

  printf("\nQual produto você quer buscar ?\n");
  scanf("%d", &codigo);
  busca_produto(l, codigo); //Busca o produto pelo código 

  printf("\nQual produto você quer excluir ?\n");
  getchar();
  scanf("%s", &nome);
  l = exclui_produto(l, nome); //Exclui o produto pelo nome

  destroi_lista(l); //Destroi a lista alocada
}