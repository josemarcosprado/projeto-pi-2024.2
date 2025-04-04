#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//struct que define um tipo para trabalharmos com as posições no "grid" do labirinto
typedef struct {
	int x;
	int y;
	} Vetor2;

//struct para guardar as informações do personagem
typedef struct {
	Vetor2 posicao;
	int forca;
	Vetor2 destino;
	} Personagem;

//struct para guardar as informações de cada elemento do labirinto
typedef struct {
	Vetor2 posicao;
	// esses ints funcionam como booleanos que armazenam o que o elemento do labirinto é e o que ele não é
	int parede;
	int chao;
	int caminhado;
	int destino;
	int inimigo;
	int inicio;
	} Elemento;

//função que cria elementos com todos os valores iguais a 0 para padronização
Elemento criaElementoZerado() {
	Elemento e = {{0, 0}, 0, 0, 0, 0, 0};
	return e;
}
//padrao de criação de uma variável "Elemento": Elemento nome_elemento = criaElementoZerado();

//função para a classificação de cada elemento: retorna o elemento com a instância "booleana" correspondente como 1 (true)
Elemento classificaElemento (char txtElemento){
	Elemento e = criaElementoZerado();
	if (txtElemento == '#') e.parede = 1;
	else if (txtElemento == '.') e.chao = 1;
	else if (txtElemento == '$') e.destino = 1;
	else if (txtElemento == '%') e.inimigo = 1;
	else if (txtElemento == '@') e.inicio = 1;
	else printf("\nElemento não reconhecido\n");

	return e;
}

//Sistema de combate: recebe um ponteiro para personagem e retorna um inteiro - 0 = derrota, 1 = vitória
int combate (Personagem *heroi) { 
	srand(time(NULL));  //inicializa o gerador de números aleatórios (seed nova a cada segundo)
    int roll = (rand() % 10)+1;
	if ((roll + heroi->forca) > 10) {
		if (heroi->forca < 10) heroi->forca++;
		return 1; //vitória no combate
	} else {
		return 0; //derota no combate
	}

}

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

int main(int argc, char** argv){ 
	
	//cria as variáveis das dimensões (n, m) e do labirinto em si (labirinto)
	int n, m;
	char labirinto[20][20];

	//recebe as dimensões e o labirinto, salvando sem os espaços
	scanf("%i", &n);
	scanf("%i", &m);
	Elemento elementos[n*m];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			fscanf(stdin, " %c", &labirinto[i][j]);
		}
	}
	
	//imprime o labirinto recebido, com base nas dimensões recebidas (n, m), com espaços
	//além disso, aproveita a iteração na matriz do labirinto para classificar seus elementos
 	printf("\n");
	for (int i = 0, k = 0; i < n; i++){
		printf("%c", labirinto[i][0]);
		elementos[k] = classificaElemento(labirinto[i][0]);
		k++;
		for (int j = 1; j < m; j++){
			j == m-1 ? printf(" %c\n", labirinto[i][j]) : printf(" %c", labirinto[i][j]);
			elementos[k] = classificaElemento(labirinto[i][j]);
			k++;
		}
	}

// //função pra fazer com que o personagem se movimente. 
// void movimento(Personagem *p1, Inimigo *i1, char mtx[20][20], int n,int m) {
//     srand(time(NULL));  //inicializa o gerador de números aleatórios (seed nova a cada segundo)
    
//     while (1) {
// 		//Gera direção (1=cima, 2=direita, 3=baixo, 4=esquerda)
// 		int direcao = (rand() % 4)+1;
// 		p1-> destino.x = p1-> posicao.x;
// 		p1-> destino.y = p1-> posicao.y;
		
// 		// Nova posição pela direção
// 		switch(direcao) {
// 			case 1: p1-> destino.x--; break; // Cima
// 			case 2: p1-> destino.y++; break; // Direita
// 			case 3: p1-> destino.x++; break; // Baixo
// 			case 4: p1-> destino.y--; break; // Esquerda
// 		}
        
//         // Verifica se a nova posição é válida
//         if (p1-> destino.x < 0 || p1-> destino.x >= n || p1-> destino.y < 0 || p1-> destino.y >= m) {
//             continue; // Posição invalida
//         }
        
//         // Verifica a nova posição
//         if (mtx[p1-> destino.x][p1-> destino.y] == '#') {
//             // Parede 
//             continue;
//         } else if (mtx[p1-> destino.x][p1-> destino.y] == '*') {
//             // Passado do personagem
//             mtx[p1->posicao.x][p1->posicao.y] = '?';
//             break;
//         } else if (mtx[p1-> destino.x][p1-> destino.y] == '%') {
//             // Inimigo
//             int resultado = combate(p1, i1);
//             if (resultado == 0) {
//                 mtx[p1-> posicao.x][p1-> posicao.y] = '+';
//                 break;
//             } else {
//                 mtx[p1-> posicao.x][p1-> posicao.y] = '!';
//                 p1-> posicao.x = p1-> destino.x;
//                 p1-> posicao.y = p1-> destino.y;
//                 mtx[p1-> destino.x][p1-> destino.y] = '@';
//             }
//         } else if (mtx[p1-> destino.x][p1-> destino.y] == '$') {
//             // chegada
//             mtx[p1-> posicao.x][p1-> posicao.y] = 'V';
//             break;
//         } else {
//             // Caminho livre
//             mtx[p1-> posicao.x][p1-> posicao.y] = '*';
//             p1-> posicao.x = p1-> destino.x;
//             p1-> posicao.y = p1-> destino.y;
//             mtx[p1-> destino.x][p1-> destino.y] = '@';
//         	}
//     	}
// 	}
	
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
