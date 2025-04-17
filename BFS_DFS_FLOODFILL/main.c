// Não ta funcionando ainda, falta a DFS, Demonstração e outras coisas.
// Usar o timer e cls pra ficar visivel e da pra ver
// Talvez colocar contador pra ver a quantidade de passos
// Mostrar ordem dos passos talvez
// Adicionar nós que não podem ser visitados, pra ver o funcionamento parecido com Flood Fill
// Botar pra busca começar de outro ponto aleatório
// Mostrar resultado completo, da matriz que iniciou e finalizou, e os passos que deu

#include <stdio.h>
#include <stdlib.h>

#include <windows.h> 

// Resultado do centro sempre arredondado pra baixo(pra 11, centro 5)
#define TAM 22

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

typedef struct {
    int x, y;
} Ponto;

typedef struct {
    Ponto itens[TAM * TAM];
    int frente, tras;
} Fila;

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
}

int filaVazia(Fila *f) {
    return f->frente == f->tras;
}

void enfileirar(Fila *f, int x, int y) {
    f->itens[f->tras].x = x;
    f->itens[f->tras].y = y;
    f->tras++;
}

Ponto desenfileirar(Fila *f) {
    return f->itens[f->frente++];
}

void imprimirMatriz(char matriz[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void bfs(char matriz[TAM][TAM], int startX, int startY) {
    Fila f;
    inicializarFila(&f);
    enfileirar(&f, startX, startY);
    matriz[startX][startY] = '*';

    while (!filaVazia(&f)) {
        Ponto atual = desenfileirar(&f);

        for (int i = 0; i < 4; i++) {
            int nx = atual.x + dx[i];
            int ny = atual.y + dy[i];

            if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM && matriz[nx][ny] == '.') {
                matriz[nx][ny] = '*'; // Marca posição como visitado (Precisa de Timer de algum tempo pra visualizar depois)
                enfileirar(&f, nx, ny);

                system("cls");
                imprimirMatriz(matriz);
                Sleep(1500); 

                // Observando com o timer alto, da pra ver que ele realiza o trabalho por camadas, e só termina quando finaliza uma camada, como explicado em aula


                // Acho que seria mais adequado pro FLOOD FILL do paint, pois "colore" de dentro pra fora uniformemente
            }
        }
    }
}

// IMPLEMENTAR DFS *****

int main() {
    char matriz[TAM][TAM];

    // Preenche matriz com '.'
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            matriz[i][j] = '.';

    int opcao;
    printf("Escolha o algoritmo:\n1 - BFS\n2 - DFS (Nao funciona)\n> ");
    scanf("%d", &opcao);

    // Por enquanto pega o meio da matriz que a gente escolhe a partir do tamanho como ponto inicial da busca

    int startX = TAM/2;
    int startY = TAM/2;


    // Faz a BFS, preenchendo com * na função e imprime a matriz (Depois coloco o timer)
    if (opcao == 1) {
        bfs(matriz, startX, startY);
        printf("\nResultado da BFS:\n");
        imprimirMatriz(matriz);
    } else {
        printf("Sem DFS ainda.\n");
    }

    return 0;
}
