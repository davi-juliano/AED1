#include <stdio.h>
#include <stdlib.h>

int ProcuraNome(char nome[], FILE *parq){
	char str[50];	
	int i;

	parq=fopen("texto.txt", "r");
	
	while(!feof(parq)){
		fscanf(parq,"%s\n", &str);
		if(strcmp(str, nome) == 0){
			i++;
		}
	}
    fclose(parq);
	return i;	
}


int main(){
	FILE *parq;
	int i, num;

	char nome1[100];
    char nome2[100];

    parq=fopen("texto.txt", "w");

    while (strcmp(nome1, "FIM") != 0) {
        scanf("%s", nome1);
        fprintf(parq, "%s\n", nome1);
	}
    fclose(parq);
    
    scanf("%s", nome2);
    num = ProcuraNome(nome2, &parq);
    printf("%d", num);
}