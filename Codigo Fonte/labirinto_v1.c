// esvcrever o código fonte do labirinto nesse arquivo aqui
#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *lab; 
	lab = fopen("teste.txt", "r");
	
	if(lab == NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		return 0;
		}
	
	char string[100];
	while(fgets(string, 100, lab) != NULL){
			printf("%s", string);
		}	
	
	fclose(lab);
	
	printf("\n");
	printf("\n");
	
	printf("Selecione o modo desejado:\n");
	printf("1. Resolver o labirinto com uma tentativa.\n");
	printf("2. Resolver o labirinto ate obter sucesso.\n");
	printf("3. Salvar o labirinto resolvido em um arquivo.\n");
	printf("4. Sair do programa.");
	return 0;
	}
