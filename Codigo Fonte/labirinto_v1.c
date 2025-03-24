// esvcrever o código fonte do labirinto nesse arquivo aqui
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void salvaLabirinto (char* nomeLab, char labirinto[20][20], int linhas) {
	FILE *lab;
	lab = fopen(strcat(nomeLab, ".txt"), "w");
	
	for (int i = 0; i < linhas; i++){
		fprintf(lab, "%s", strcat(labirinto[i], "\n"));
	}
	
	fclose(lab);
	
	printf("\nArquivo Salvo!\n");
}

int main(int argc, char** argv){ 
	
	int n, m;
	char labirinto[20][20];
	scanf("%i", &n);
	scanf("%i", &m);
	for (int i = 0; i < n; i++){
		scanf("%s", labirinto[i]);
	}
	
	printf("\n");
	for (int i = 0; i < n; i++){
		printf("%s\n", labirinto[i]);
	}

	int sair = 0;
	while (sair == 0){
		printf("\n\n");
	
		printf("Selecione o modo desejado:\n");
		printf("1. Resolver o labirinto com uma tentativa.\n");
		printf("2. Resolver o labirinto ate obter sucesso.\n");
		printf("3. Salvar o labirinto resolvido em um arquivo.\n");
		printf("4. Sair do programa.\n");
		
		char enter, modo;
		scanf("%c", &enter);
		scanf("%c", &modo);

		switch (modo)
		{
			case '3': salvaLabirinto(argv[1], labirinto, n); break;
			case '4': sair = 1; break;
			default: printf ("\nValor invalido!\n");
		}
	}
	
	return 0;
}
