#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILA 100
typedef struct FILA{  //Estrutra da Fila
    int id[MAX_FILA];  
    int itens [MAX_FILA];
    int n; 
    int ini;
}TFila;

typedef TFila *PFila;

PFila cria_fila(){  //Função de Criação da Fila
    PFila fila = (PFila) malloc (sizeof (TFila));
    fila->n = 0;
    fila->ini = 0;
    return (fila);
}

void libera_fila(PFila fila){ //Função para liberar a fila
    free(fila);
    return;
}


int insere (PFila p, int val1, int val2){  //Função que insere algum valor na fila
    int fim;
    if (p == NULL) {
        printf("Fila não inicializada!\n");
        return -1; 
    }
    if (p->n == MAX_FILA ){
        printf("Fila cheia!\n");
        return -1; 
    }
    fim = (p->ini+p->n)%MAX_FILA;
    p->itens[fim] = val1;
    p->id[fim] = val2;
    p->n++;
    return 0; 
}

int incr_indice(int i){
    return (i+1)%MAX_FILA;
}

void insere_candidatos(PFila p ,int candidatos){
    int i=0, id=0, nota=0, j=0;

    for(i=0;i<candidatos;i++){
        id=0;
        nota=0;
        j=0;
        
        printf("Número Identificador do Candidato:"); //Recebe um ID para um candidato
        scanf("%d", &id);
        
        while(j<MAX_FILA){ //Laço para percorrer os j numeros do MAX_FILA
            while(id == p->id[j]){ //Laço para comparar o termo a termo, ou seja, se ja tiver um valor, ele não sai do laço
                printf("Já existe um candidato com esse ID, digite outro ID:");
                scanf("%d", &id);
            }
            j++;
        }  
        
        printf("Nota do candidato:");
        scanf("%d", &nota);
        
        while(0 > nota || nota > 100){ //Não sai do laço enquanto a nota não estiver entre o intervalo
            printf("Nota Inválida, insira outra:");
            scanf("%d", &nota);
        }
        
        insere(p, nota, id);  //Invoca insere para inserir à fila
        printf("Candidato Inserido!\n");
    }
}

void ordena_fila(PFila p, int candidatos){ 
    int i, j, aux1, aux2;
    
    if(candidatos == 0){ //Caso não tenha candidatos, imprime a mensagem de não ter candidatos inseridos
        printf("Não há candidatos inseridos!");
        return ;
    }
    
    for(i=0; i<candidatos; i++){  //Criação do laço que ordena todos os membros da fila, comparando eles 2 a 2
        for(j=i+1; j<candidatos; j++){
            if(p->itens[i] < p->itens[j]){
                aux1 = p->itens[i];
                aux2 = p->id[i];
                p->itens[i] = p->itens[j];;
                p->id[i] = p->id[j];;
                p->itens[j] = aux1;
                p->id[j] = aux2;
            }
        }
    }
return ;
}

void respostas(PFila p, int vagas, int classificados[]){
    int i=0, k=0;
    char resposta;
    
    while(k!=vagas){ //Printa em ordem de nota as respostas recebidas de cada um dos candidatos
      getchar();  //Para limpar o buffer do teclado
      printf("\nResposta recebido do candidato de id %d (s/n):", p->id[i]);
      scanf("%c", &resposta);

      if(resposta =='s'){
        classificados[k] = p->id[i];
        k++; //Se as vagas ja foram completadas, ele automaticamente sai do while
      }
      i++; //O i é a variável que vai percorrer pela fila, buscando apenas o ID, 
           //visto que a nota não é mais necessária por causa da ordenação
    }
    return;
}

int main(){
  int candidatos=0, vagas=0, i, id=0, nota=0, j=0, k=0;
  int classificados[MAX_FILA];
  PFila p;
    
  printf("Quantidade de Candidatos:");
  scanf("%d", &candidatos);
    
  printf("Quantidade de Vagas:");
  scanf("%d", &vagas);
    
  p = cria_fila();
  
  insere_candidatos(p, candidatos); //Invoca a função de inserir candidatos

  ordena_fila(p, candidatos); //Invoca a função de ordenar a fila
    
  for(i=0;i<candidatos;i++){ //Laço que printa os candidatos ordenados pelas notas
    printf("\nCandidato %d, nota: %d", p->id[i], p->itens[i]);
  }

  respostas(p, vagas, classificados); //Invoca a função de respostas

  printf("-Lista de Alunos Novos-");

  for(i=0;i<vagas;i++){ //Laço que printa a lista de alunos 
    printf("\nCandidato id: %d,", classificados[i]);
  }

  libera_fila(p);

}