#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//struct que define um tipo para trabalharmos com as posições no "grid" do labirinto
typedef struct 
{
	int x;
	int y;
} Vetor2;
	
	Vetor2 posicaoInicial;  // Isso declara a variável (escopo mais global, será utilizada adiante)

//struct para guardar as informações do personagem
typedef struct 
{
	Vetor2 posicao;
	int forca;
	Vetor2 destino;
} Personagem;

//struct para guardar as informações de cada elemento do labirinto
typedef struct 
{
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
Elemento criaElementoZerado() 
{
	Elemento e = {{0, 0}, 0, 0, 0, 0, 0};
	return e;
}
//padrao de criação de uma variável "Elemento": Elemento nome_elemento = criaElementoZerado();

//função para a classificação de cada elemento: retorna o elemento com a instância "booleana" correspondente como 1 (true)
Elemento classificaElemento (char txtElemento)
{
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
int combate (Personagem *heroi) 
{
	srand(time(NULL));  //inicializa o gerador de números aleatórios (seed nova a cada segundo)
    int roll = (rand() % 10)+1;
	if ((roll + heroi->forca) > 10) 
	{
		if (heroi->forca < 10) heroi->forca++;
		return 1; //vitória no combate
	} else 
	{
		return 0; //derota no combate
	}

}

//função feita para salvar o conteúdo de uma matriz num arquivo
void salvaLabirinto (char* nomeLab, char labirinto[20][20], int linhas, int colunas) 
{
	FILE *lab;
	lab = fopen(strcat(nomeLab, ".txt"), "w");
	
	for (int i = 0; i < linhas; i++)
	{
		fprintf(lab, "%c", labirinto[i][0]);
		for (int j = 1; j < colunas; j++)
		{
			j == colunas-1 ? fprintf(lab, " %c\n", labirinto[i][j]) : fprintf(lab, " %c", labirinto[i][j]);
		}
	}
	
	fclose(lab);
	
	printf("\nArquivo Salvo!\n");
}

void embaralhar(int *v, int n) 
{
    for (int i = n - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1); // índice aleatório entre 0 e i
        // troca v[i] com v[j]
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

//função que imprime o labirinto
void imprimeLabirinto(char labirinto[20][20], Personagem heroi, int linhas, int colunas) 
{
    //Percorre todas as linhas do lab.
    for (int i = 0; i < linhas; i++) 
    {
		//percorre todas as colunas do lab.
        for (int j = 0; j < colunas; j++) 
        {
            if (i == heroi.posicao.x && j == heroi.posicao.y) //Checa se a posição atual corresponde com a do personagem
            { 
                printf("@ "); // Implementa o caractere representando o personagem
            } else 
            {
                printf("%c ", labirinto[i][j]); //Se nao for o personagem imprime o caractere correspondente
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Função que cria uma pausa temporária
void pausa(int ms) 
{
    clock_t inicio = clock(); // Marca o tempo inicial
    while ((clock() - inicio) < ms * CLOCKS_PER_SEC / 1000); // Aguarda o tempo especificado
}
//substituição do void por int, já que a função vai retornar um valor indicando o resultado da tentativa do herói
int movimentoAleatorio(Personagem *heroi, Elemento *e, char labirinto[20][20], int linhas, int colunas)
{
    srand(time(NULL) + rand());
    
    int perdeu = 0;  // "booleano" para saber se o herói perdeu a luta
    int perdido = 0; // "booleano" para saber se o herói se perdeu
    
    // Continua enquanto o herói não alcançar o destino
    while(e[(heroi->posicao.x * colunas) + heroi->posicao.y].destino == 0) 
    {
        int ordem[] = {1, 2, 3, 4};
        srand(time(NULL));
        embaralhar(ordem, 4);

        Vetor2 posNova = {heroi->posicao.x, heroi->posicao.y};
        int andou = 0;
        int i = 0;

		// Tenta mover o herói até que ele consiga ou esgote as possibilidades
        while (andou == 0 && i < 4) 
        {
            switch (ordem[i]) 
            {
                case 1: posNova.x--; break; // Para cima
                case 2: posNova.y++; break; // Para direita
                case 3: posNova.x++; break; // Para baixo
                case 4: posNova.y--; break; // Para esquerda
            }

			// Verifica se o movimento é válido dentro do labirinto
            if (posNova.x >= 0 && posNova.x < linhas && posNova.y >= 0 && posNova.y < colunas &&
                e[(posNova.x * colunas) + posNova.y].parede == 0 && e[(posNova.x * colunas) + posNova.y].caminhado == 0 &&
                labirinto[posNova.x][posNova.y] != '*' && labirinto[posNova.x][posNova.y] != '!' &&
                labirinto[posNova.x][posNova.y] != '+') 
                {
                    if(labirinto[heroi->posicao.x][heroi->posicao.y] == '.') 
                    {
						labirinto[heroi->posicao.x][heroi->posicao.y] = '*';
					}
                    if (e[(posNova.x * colunas) + posNova.y].inimigo == 1)//checa se a proxima posicao é um inimigo
                    {
                        if(combate(heroi)==1)// em caso de vitoria, o personagem segue seu caminho normalmente
                        {
                            e[(posNova.x * colunas) + posNova.y].inimigo = 0;
                            e[(posNova.x * colunas) + posNova.y].caminhado = 1;//Mesmo sendo um inimigo marca que o heroi já percorreu
                            labirinto[posNova.x][posNova.y] = '!'; //atualiza o caractere do inimigo morto
                            heroi->posicao = posNova; // Atualiza a posição do herói
                            andou = 1; // Indica que o movimento foi bem-sucedido
							
							labirinto[posicaoInicial.x][posicaoInicial.y] = '@';
                            pausa(500); // Substitui Sleep 
                            imprimeLabirinto(labirinto, *heroi, linhas, colunas);
                        } 
                        else
                        {
                            //Se o combate é perdido o jogo acaba
                            printf("\nO heroi perdeu a luta...\n");
                            labirinto[posNova.x][posNova.y] = '+';
                            imprimeLabirinto(labirinto, *heroi, linhas, colunas);
                            perdeu = 1; // Indica derrota do Personagem
                            andou = 1; // Impede que a leitura seja que o Personagem se perdeu
                            break;
                            
                        }
                                    
                    }
                    else
                    {
						if (labirinto[heroi->posicao.x][heroi->posicao.y] != '!' && labirinto[heroi->posicao.x][heroi->posicao.y] != '+')
						{
							labirinto[heroi->posicao.x][heroi->posicao.y] = '*'; // Marca como caminho percorrido
						}
                        e[(heroi->posicao.x * colunas) + heroi->posicao.y].caminhado = 1;
					
                        heroi->posicao = posNova;
                        andou = 1; // Indica que o movimento foi bem-sucedido
						
                        pausa(500); // Substitui Sleep
                        labirinto[posicaoInicial.x][posicaoInicial.y] = '@'; 
                        imprimeLabirinto(labirinto, *heroi, linhas, colunas);
                    } 
                }
            
            else 
            {
				// Se o movimento não é válido, restaura a posição inicial
                posNova = (Vetor2){heroi->posicao.x, heroi->posicao.y};
                i++; // Tenta a próxima direção
            }
        }
        
        if(perdeu == 1 ) //Impede que a leitura seja que o Personagem se perdeu
        {
            break;
        }

        if (andou == 0) 
        {
            printf("\nO heroi se perdeu...\n");
            if(labirinto[heroi->posicao.x][heroi->posicao.y] != '!')
            {
				labirinto[heroi->posicao.x][heroi->posicao.y] = '?'; //se o personagem se perder e nao estiver em cima de um inimigo, ele irá virar uma interrogação
			}
            perdido = 1;
            break;
        }
    }

    if (perdido == 0 && perdeu == 0) 
    {
		printf("\nO heroi chegou ao destino!\n");
		labirinto[heroi->posicao.x][heroi->posicao.y] = 'v'; // qnd o personagem alcança o objetivo, ele se torna um v
	}
    
    if (perdeu == 1) return -1; //morreu
    if (perdido == 1) return 0; //se perdeu
    return 1; //chegou ao destino
}

int main(int argc, char** argv)
{ 
	//cria as variáveis das dimensões (n, m) e do labirinto em si (labirinto)
	int n, m;
	char labirinto[20][20];
	int maxTentativas = 20; //estabelecendo o numero maximo de tentativas permitido
	int tentativas = 0;
	printf("Insira o labirinto com suas dimensoes:\n");

	//recebe as dimensões e o labirinto, salvando sem os espaços
	scanf("%i", &n);
	scanf("%i", &m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fscanf(stdin, " %c", &labirinto[i][j]);
		}
	}
	
	//imprime o labirinto recebido, com base nas dimensões recebidas (n, m), com espaços
	//além disso, aproveita a iteração na matriz do labirinto para classificar seus elementos	
	Elemento elementos[n][m];
 	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("%c", labirinto[i][0]);
		elementos[i][0] = classificaElemento(labirinto[i][0]);
		elementos[i][0].posicao = (Vetor2){i, 0};
		for (int j = 1; j < m; j++)
		{
			j == m-1 ? printf(" %c\n", labirinto[i][j]) : printf(" %c", labirinto[i][j]);
			elementos[i][j] = classificaElemento(labirinto[i][j]);
			elementos[i][j].posicao = (Vetor2){i, j};
		}
	}

	//cria o personagem básico e preenche as informações que ele "sabe" de acordo com cada elemento do struct
	Personagem heroi = {{0, 0}, 5, {0, 0}}; //posicao do heroi zerada, força = 5 (50% de chance em combate), e posicao do destino zerada
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (elementos[i][j].inicio == 1)
			{
				heroi.posicao = elementos[i][j].posicao; //preenche a posiçao de inicio do heroi
				 posicaoInicial = heroi.posicao; // Salva a posição inicial para referência
			} else if (elementos[i][j].destino == 1)
			{
				heroi.destino = elementos[i][j].posicao; //preenche o destino do heroi
			}
		}
	}
	
	// Salva a posição inicial do herói para resetar depois
	Vetor2 posicaoInicial = heroi.posicao;
	//"menu" de controle principal do código, após receber o labirinto
	
	int sair = 0; //variável tratada como booleana, false até que '4' seja selecionado
	int sucesso = 0; // variável que irá controlar o loop
	while (sair == 0)
	{
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
			case '1': 
				heroi.forca = 5; //a cada loop reseta a força inicial do personagem para seu valor inicial de 5
				for (int i = 0; i < n; i++) 
				{
			     for (int j = 0; j < m; j++) 
			     {
				  if (labirinto[i][j] == '*' || labirinto[i][j] == '?') 
				  {
					labirinto[i][j] = '.';  // limpa caminhos e mortes
				  } else if (labirinto[i][j] == '!' || labirinto[i][j] == '+')//Limpa os inimigos e faz eles voltarem a ser %
				  { 
					labirinto[i][j] = '%';
				  } else if (labirinto[i][j] == 'v')
				   {
					   labirinto[i][j] = '$';
				   }
				elementos[i][j] = classificaElemento(labirinto[i][j]);
				elementos[i][j].posicao = (Vetor2){i, j};
				 }
				}	

			// Volta pra posição inicial salva
			heroi.posicao = posicaoInicial;
			movimentoAleatorio(&heroi, &elementos[0][0], labirinto, n, m); 
			break;
				
			case '2':
	            while (sucesso == 0 && tentativas < maxTentativas) 
	            {
				heroi.forca = 5;
		        // Resetar o labirinto
		         for (int i = 0; i < n; i++) 
		         {
			      for (int j = 0; j < m; j++) 
			      {
				   if (labirinto[i][j] == '*' || labirinto[i][j] == '?') 
				   {
					 labirinto[i][j] = '.';
				   } else if (labirinto[i][j] == '!' || labirinto[i][j] == '+')
				   { 
					 labirinto[i][j] = '%';
				   } else if (labirinto[i][j] == 'v')
				   {
					   labirinto[i][j] = '$';
				   }
				   elementos[i][j] = classificaElemento(labirinto[i][j]);
				   elementos[i][j].posicao = (Vetor2){i, j};
				  }
				}

			      
			      heroi.posicao = posicaoInicial;

			      // Executa a tentativa
			      int resultado = movimentoAleatorio(&heroi, &elementos[0][0], labirinto, n, m);
			      if (resultado == 1) 
			      {
			        sucesso = 1;
			      } else 
			      {  
					  tentativas++;
				  }
				}
				if (tentativas >= maxTentativas) //caso o personagem nao complete o labirinto no numero maximo de tentativas, o programa volta ao menu
				{
					printf("\nNumero maximo de tentativas alcancado. O heroi foi incapaz de vencer!\n");
				}
			break;
			case '3': salvaLabirinto(argv[1], labirinto, n, m); break;
			case '4': sair = 1; break;
			default: printf ("\nValor invalido!\n");
		}
	}

	return 0;
}

