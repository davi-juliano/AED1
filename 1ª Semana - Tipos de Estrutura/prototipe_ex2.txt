#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char nome[50];
	int idade;
	float altura;
}Pessoa;

void ImprimaDados(Pessoa *pessoas){
    printf("%s", pessoas->nome);
    printf("\n%d", pessoas->idade);
    printf("\n%f", pessoas->altura);
    free(pessoas);
    
}

int main(){
	Pessoa *pessoas;

pessoas=(Pessoa*)malloc(sizeof(Pessoa));

gets(&pessoas->nome);
scanf ("%d", &pessoas->idade);
scanf ("%f", &pessoas->altura);

ImprimaDados(pessoas);

}