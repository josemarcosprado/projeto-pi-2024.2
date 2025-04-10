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

void embaralhar(int *v, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1); // índice aleatório entre 0 e i
        // troca v[i] com v[j]
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

//Função responsável por movimentar o personagem aleatoriamente pelo labirinto, até chegar no destino, ou se perder:
void movimentoAleatorio(Personagem *heroi, Elemento *e, int linhas, int colunas){
	int perdido = 0; //"booleano" para saber se o herói se perdeu
	//Enquanto o elemento cuja posição é igual à do herói não for o destino, ele tenta de novo:
	while(e[(heroi->posicao.x * colunas) + heroi->posicao.y].destino == 0){
		//gera uma sequência aleatória de tentativas
		int ordem[] = {1, 2, 3, 4};
		srand(time(NULL)); //inicia o gerador para embaralhar a ordem de tentativas
		embaralhar(ordem, 4); //embaralha a lista "ordem"
		//tenta, na sequencia se movimentar para cada uma das posições
		Vetor2 posNova = {heroi->posicao.x, heroi->posicao.y}; //vetor inicializado com a posicao atual do heroi
		int andou = 0; // "booleano" pra saber se o heroi andou ou se perdeu
		int i = 0; //contador
		while (andou == 0 && i < 4){		
			switch (ordem[i]){ //tenta a posição i da ordem aleatória:
				case 1: posNova.x--; break; //Para cima (Norte)
				case 2: posNova.y++; break; //Para direita (Leste)
				case 3: posNova.x++; break; //Para baixo (Sul)
				case 4: posNova.y--; break; //Para esquerda (Oeste)
			}

			//verifica se a posição nova é válida (está na matriz e não é parede ou caminho já andado)
			if (posNova.x >= 0 && posNova.x < linhas && posNova.y >= 0 && posNova.y < colunas && e[(posNova.x * colunas) + posNova.y].parede == 0 && e[(posNova.x * colunas) + posNova.y].caminhado == 0){
				//caso seja válida:
				e[(heroi->posicao.x * colunas) + heroi->posicao.y].caminhado = 1; //torna a posição anterior como "caminhada"
				heroi->posicao = posNova; //move o heroi para a posição nova
				andou = 1; //"avisa" ao loop que o herói andou, e portanto, pode parar de tentar para essa posição
			} else {
				//caso não seja válida:
				posNova = (Vetor2) {heroi->posicao.x, heroi->posicao.y}; //volta para a posição anterior
				i++; //aumenta o contador
			}
		}
		if (andou == 0) {
			//Caso o loop acima termine e o personagem não tenha andado, pressupõe-se que ele se perdeu. Nesse caso:
			printf("\nO herói se perdeu...\n"); //Imprime que o herói se perdeu
			perdido = 1; //Torna o "booleano" perdido = true
			break; //Sai do loop que tenta até chegar no destino
		}
	}
	if (perdido == 0) printf("\nO herói chegou ao destino!\n"); //Caso saia do loop e não tenha se perdido, o herói chegou ao destino!
}
	
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
	//além disso, aproveita a iteração na matriz do labirinto para classificar seus elementos	
	Elemento elementos[n][m];
 	printf("\n");
	for (int i = 0; i < n; i++){
		printf("%c", labirinto[i][0]);
		elementos[i][0] = classificaElemento(labirinto[i][0]);
		elementos[i][0].posicao = (Vetor2){i, 0};
		for (int j = 1; j < m; j++){
			j == m-1 ? printf(" %c\n", labirinto[i][j]) : printf(" %c", labirinto[i][j]);
			elementos[i][j] = classificaElemento(labirinto[i][j]);
			elementos[i][j].posicao = (Vetor2){i, j};
		}
	}

	//cria o personagem básico e preenche as informações que ele "sabe" de acordo com cada elemento do struct
	Personagem heroi = {{0, 0}, 5, {0, 0}}; //posicao do heroi zerada, força = 5 (50% de chance em combate), e posicao do destino zerada
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (elementos[i][j].inicio == 1){
				heroi.posicao = elementos[i][j].posicao; //preenche a posiçao de inicio do heroi
			} else if (elementos[i][j].destino == 1){
				heroi.destino = elementos[i][j].posicao; //preenche o destino do heroi
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
			case '1': movimentoAleatorio(&heroi, &elementos[0][0], n, m); break;
			case '3': salvaLabirinto(argv[1], labirinto, n, m); break;
			case '4': sair = 1; break;
			default: printf ("\nValor invalido!\n");
		}
	}

	return 0;
}
