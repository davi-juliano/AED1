#include<stdio.h>
#include<stdlib.h>

//Davi Juliano Ferreira Alves - 133595 - Turma N

int main (){
	int num_candidatos, i=0,j=1, voto=1;
	int *votos;
    
	printf("Qual é o numero de candidatos?\n");

	scanf("%d",&num_candidatos);

	//Se o numero de candidatos é igual a 0, não tem candidatos pra disputar a eleição
	if(num_candidatos == 0)
		return 0;
	
	//Alocação Dinâmica
	votos=(int*)malloc(num_candidatos * sizeof(int));
	

	//Tornando o vetor de votos um vetor de zeros
	while(i > num_candidatos)
		votos[i] = 0;

	i = 0;

    //Função que coloca os votos nos respectivos lugares do vetor de candidatos
	while(voto >0){
		scanf("%d",&voto);

		while(voto>num_candidatos){
		    printf("Voto Invalido\n");
		    scanf("%d",&voto);
		}
		
	    if(voto<0){
            	break;
        }
		(votos[voto-1])++; //não de 0 a n-1
		
	}		
    
    //Função de contagem e comparação 2 a 2
	while(j<num_candidatos){
		if(votos[i]<=votos[j]){
			i = j;
			j++;
		}
		else{
			j++;
		}
	}
    
    //Fazendo a readequação do índice de contagem
	i++;

	printf("O vencedor é o candidato: %d",i);
	free(votos);
}