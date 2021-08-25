#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char nome[50];
	int idade;
	float altura;
}Pessoa;

void ImprimaDados(Pessoa *pessoas[], int i){
    printf("\n%s", pessoas[i]->nome);
    printf("\n%d", pessoas[i]->idade);
    printf("\n%.2f", pessoas[i]->altura);
    free(pessoas[i]);    
}

int main(){
	int i, TAM;

	scanf("%d", &TAM);

	Pessoa *pessoas[TAM];



for(i=0;i<TAM;i++){
	pessoas[i]=(Pessoa*)malloc(sizeof(Pessoa));
	scanf ("%s", &pessoas[i]->nome);
	scanf ("%d", &pessoas[i]->idade);
	scanf ("%f", &pessoas[i]->altura);
}

for(i=0;i<TAM;i++){
	ImprimaDados(pessoas, i);
}
}