// esvcrever o código fonte do labirinto nesse arquivo aqui
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//função feita para salvar o conteúdo de uma matriz num arquivo
void salvaLabirinto (char* nomeLab, char labirinto[20][20], int linhas, int colunas) {
	FILE *lab;
	lab = fopen(strcat(nomeLab, ".txt"), "w");
	
	for (int i = 0; i < linhas; i++){
		fprintf(lab, "%c", labirinto[i][0]);
		for (int j = 1; j < colunas; j++){
			j == colunas-1 ? fprintf(lab, " %c\n", labirinto[i][j]) : fprintf(lab, " %c", labirinto[i][j]);
		}
	}
	
	fclose(lab);
	
	printf("\nArquivo Salvo!\n");
}

//struct para guardar as informações do personagem
struct personagem{
	int posicao[2];
	int ultposicao[2];
	int destino[2];
	};

typedef struct personagem personagem;

//struct para guardar as informações de cada elemento do labirinto
struct elemento{
	int posicao[2];
	int parede;
	int passado;
	int inimigo;
	};

typedef struct elemento elemento;

int main(int argc, char** argv){ 
	
	//cria as variáveis das dimensões (n, m) e do labirinto em si (labirinto)
	int n, m;
	char labirinto[20][20];

	//recebe as dimensões e o labirinto, salvando sem os espaços
	scanf("%i", &n);
	scanf("%i", &m);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			fscanf(stdin, " %c", &labirinto[i][j]);
		}
	}
	
	//imprime o labirinto recebido, com base nas dimensões recebidas (n, m), com espaços
 	printf("\n");
	for (int i = 0; i < n; i++){
		printf("%c", labirinto[i][0]);
		for (int j = 1; j < m; j++){
			j == m-1 ? printf(" %c\n", labirinto[i][j]) : printf(" %c", labirinto[i][j]);
		}
	}
	
	//Reconhece e imprime os elementos do labirinto (Protótipo)
	for (int i = 0; i < n; i++){
		for (int j = 1; j < m; j++){
			if(labirinto[i][j] == '#'){
				printf("\nelemento(%i,%i) : Parede", i, j);
			}
			else if(labirinto[i][j] == '@'){
				printf("\nelemento%i,%i: Personagem",i,j );
			}
			else if(labirinto[i][j] == '$'){
				printf("\nelemento%i,%i: Chegada",i,j );
			}
			else if(labirinto[i][j] == '.'){
				printf("\nelemento%i,%i: Caminho",i,j );
			}
			else if(labirinto[i][j] == '%'){
				printf("\nelemento%i,%i: Inimigo",i,j );
			}
		}
	}
	
	
	//"menu" de controle principal do código, após receber o labirinto
	int sair = 0; //variável tratada como booleana, false até que '4' seja selecionado
	while (sair == 0){
		//escreve as opções de uso do programa na tela
		printf("\n\n");
	
		printf("Selecione o modo desejado:\n");
		printf("1. Resolver o labirinto com uma tentativa.\n");
		printf("2. Resolver o labirinto ate obter sucesso.\n");
		printf("3. Salvar o labirinto resolvido em um arquivo.\n");
		printf("4. Sair do programa.\n");
		
		//recebe o input do usuário
		char enter, modo;
		scanf("%c", &enter);
		scanf("%c", &modo);

		//processa o input do usuário
		switch (modo)
		{
			case '3': salvaLabirinto(argv[1], labirinto, n, m); break;
			case '4': sair = 1; break;
			default: printf ("\nValor invalido!\n");
		}
	}
	
	return 0;
}
