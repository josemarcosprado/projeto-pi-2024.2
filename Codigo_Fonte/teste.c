#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void embaralhar(int *v, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1); // índice aleatório entre 0 e i
        // troca v[i] com v[j]
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

 //função pra fazer com que o personagem se movimente 
 void movimento(Personagem *p, Elemento *e, int colunas) {
    srand(time(NULL));  //inicializa o gerador de números aleatórios (seed nova a cada segundo)
    
    while (1) {
		//Vai na matriz de elementos e altera o status do elemento no qual o personagem está pisando para "caminhado"
 		e[(p->posicao.x * colunas) + p->posicao.y].caminhado = 1;
		e[(p->posicao.x * colunas) + p->posicao.y].chao = 0;
		e[(p->posicao.x * colunas) + p->posicao.y].inicio = 0;
		
		//Gera direção (1=cima, 2=direita, 3=baixo, 4=esquerda)
 		int direcao = (rand() % 4)+1;
 		//Nova posição pela direção aleatória		
		Vetor2 posNova;
 		switch(direcao) {
 			case 1: posnova = (Vetor2) {p->posicao.x-1, p->posicao.y}; break; // Cima
 			case 2: posnova = (Vetor2) {p->posicao.x, p->posicao.y+1}; break; // Direita
 			case 3: posnova = (Vetor2) {p->posicao.x+1, p->posicao.y}; break; // Baixo
 			case 4: posnova = (Vetor2) {p->posicao.x, p->posicao.y-1}; break; // Esquerda
 		}
        
         // Verifica se a nova posição é válida
         if (p1-> destino.x < 0 || p1-> destino.x >= n || p1-> destino.y < 0 || p1-> destino.y >= m) {
             continue; // Posição invalida
         }
        
         // Verifica a nova posição
         if (mtx[p1-> destino.x][p1-> destino.y] == '#') {
             // Parede 
             continue;
         } else if (mtx[p1-> destino.x][p1-> destino.y] == '*') {
             // Passado do personagem
             mtx[p1->posicao.x][p1->posicao.y] = '?';
             break;
         } else if (mtx[p1-> destino.x][p1-> destino.y] == '%') {
             // Inimigo
             int resultado = combate(p);//eliminação de um argumento devido a problema no compilador
             if (resultado == 0) {
                 mtx[p1-> posicao.x][p1-> posicao.y] = '+';
                 break;
             } else {
                 mtx[p1-> posicao.x][p1-> posicao.y] = '!';
                 p1-> posicao.x = p1-> destino.x;
                 p1-> posicao.y = p1-> destino.y;
                 mtx[p1-> destino.x][p1-> destino.y] = '@';
             }
         } else if (mtx[p1-> destino.x][p1-> destino.y] == '$') {
             // chegada
             mtx[p1-> posicao.x][p1-> posicao.y] = 'V';
             break;
         } else {
             // Caminho livre
             mtx[p1-> posicao.x][p1-> posicao.y] = '*';
             p1-> posicao.x = p1-> destino.x;
             p1-> posicao.y = p1-> destino.y;
            mtx[p1-> destino.x][p1-> destino.y] = '@';
         	}
     	}
 	}

int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    int v[] = {1, 2, 3, 4};
    int n = sizeof(v) / sizeof(v[0]);

    embaralhar(v, n);

    printf("Sequência embaralhada: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    return 0;
}

