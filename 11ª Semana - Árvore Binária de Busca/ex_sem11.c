#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arv{
    int info;
    struct arv* esq;
    struct arv*dir;
}TArv;
typedef TArv *PArv;

PArv insereABB (PArv a, int c){     //Função que insere um valor na ABB
    if (a == NULL) {  //Há uma diferença no código do slide, para evitar inserir o mesmo valor duas vezes
        PArv novo=(PArv)malloc(sizeof(TArv));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->info = c;
        a = novo;
    }

    else if (c < a->info)
        a->esq = insereABB(a->esq,c);
    else if (c > a->info)  //Eis a diferença, pois não queremos valores repetidos na ABB
        a->dir = insereABB(a->dir,c);
    else{
        return(a);
    }
}

PArv buscaABB(PArv a, int c){ //Função que busca um nó de acordo com o dado dele na ABB
    if (a==NULL)
        return NULL; 
    
    else if(c < a->info)
        return(buscaABB(a->esq,c));
    
    else if (c > a->info)
        return(buscaABB(a->dir,c));
    
    else
        return a;
    
}

int verif_se_ABB(PArv a){ //Função que verifica se é uma ABB
    PArv prox=NULL;
    if(a){
        if (!verif_se_ABB(a->esq)){
          return 0;
        }
        if(prox != NULL && a->info <= prox->info){ //Analisa justamente da esquerda para a direita
            return 0;
        }
        prox = a;
        return verif_se_ABB(a->dir); //Usando recursão para analisar a direita
    }
    return 1;
}

PArv une_ABB(PArv a, PArv b){  //Função que une ABB's
    PArv c = a;    //Utiliza uma árvore auxiliar
    
    if(b==NULL){  //Se b for NULL, ele retorna a (Caso trivial)
        return a;
    }
    if((c = buscaABB(c, b->info)) == NULL){ //Se não existe esse valor de b em a, ele adiciona
        insereABB(a,b->info);
    }
    une_ABB(a,b->esq); //Varre b inteiro
    une_ABB(a,b->dir);
}