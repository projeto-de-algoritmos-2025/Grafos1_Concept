// BFS, DFS E FLOOD FILL (Genilson Silva e Carlos Eduardo)

#include <stdio.h>
#include <stdlib.h>

#include <windows.h> 

// Resultado do centro sempre arredondado pra baixo(pra 11, centro 5)
#define TAM 11

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

typedef struct {
    int x, y;
} Ponto;


//  Fila para BFS
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

//  Pilha usada na DFS
typedef struct {
    Ponto itens[TAM * TAM];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, int x, int y) {
    p->topo++;
    p->itens[p->topo].x = x;
    p->itens[p->topo].y = y;
}

Ponto desempilhar(Pilha *p) {
    return p->itens[p->topo--];
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

// Função da BFS Com o Timer e CLS

void bfs(char matriz[TAM][TAM], int startX, int startY) {
    Fila f;
    inicializarFila(&f);
    enfileirar(&f, startX, startY);
    matriz[startX][startY] = '*';

    int passos = 0;
    int passostotais = 0;

    while (!filaVazia(&f)) {
        Ponto atual = desenfileirar(&f);

        for (int i = 0; i < 4; i++) {
            int nx = atual.x + dx[i];
            int ny = atual.y + dy[i];

            passostotais++;

            if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM && matriz[nx][ny] == '.') {
                matriz[nx][ny] = '*'; // Marca posição como visitado
                enfileirar(&f, nx, ny);
                passos++;

                system("cls");
                imprimirMatriz(matriz);
                printf("Quantidade de Pontos Visitados: %d\n", passos);
                printf("Quantidade de Passos totais: %d\n", passostotais);
                Sleep(300);

                // Observando com o timer alto, da pra ver que ele realiza o trabalho por camadas, e só termina quando finaliza uma camada, como explicado em aula

                // Acho que seria mais adequado pro FLOOD FILL do paint, pois "colore" de dentro pra fora uniformemente
            }
        }
    }
}

// Função da DFS Com o Timer e CLS

void dfs(char matriz[TAM][TAM], int startX, int startY) {
    Pilha p;
    inicializarPilha(&p);
    empilhar(&p, startX, startY);

    int passos = 0;
    int passostotais = 0;

    while (!pilhaVazia(&p)) {
        Ponto atual = desempilhar(&p);

        passostotais++;

        // Verifica se já foi visitado
        if (matriz[atual.x][atual.y] == '*' || matriz[atual.x][atual.y] == '#') continue;

        matriz[atual.x][atual.y] = '*';

        passos++;

        // Exibe o passo
        system("cls");
        imprimirMatriz(matriz);

        printf("Quantidade de Pontos Visitados: %d\n", passos);
        printf("Quantidade de Passos totais: %d\n", passostotais);

        Sleep(300);

        for (int i = 3; i >= 0; i--) {
            int nx = atual.x + dx[i];
            int ny = atual.y + dy[i];

            if (nx >= 0 && nx < TAM && ny >= 0 && ny < TAM && matriz[nx][ny] == '.') {
                empilhar(&p, nx, ny);

                // Seguindo um caminho até o fim e volta (backtracking), como abordado em sala, sendo útil para puzzles e labirintos.

            }
        }
    }
}

int main() {
    char matriz[TAM][TAM];

    // Preenche toda a matriz com '.' para indicar posições não visitadas
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            matriz[i][j] = '.';

    int opcaoBusca;

    // Solicita ao usuário que escolha entre os algoritmos BFS ou DFS
    printf("Escolha o algoritmo:\n1 - BFS\n2 - DFS\n> ");
    scanf("%d", &opcaoBusca);

    if (opcaoBusca != 1 && opcaoBusca != 2) {
        printf("Opcao invalida.\n");
        return 1;
    }

    int tipoInicio;
    printf("\nEscolha o tipo de inicio:\n1 - Comecar do centro da matriz\n2 - Escolher a posicao inicial\n> ");
    scanf("%d", &tipoInicio);

    int startX, startY; // Variáveis que armazenam as coordenadas iniciais

    if (tipoInicio == 1) {

        // Define o ponto inicial como o centro da matriz
        startX = TAM / 2;
        startY = TAM / 2;
    } else if (tipoInicio == 2) {
        printf("Digite a linha inicial (0 a %d): ", TAM - 1);
        scanf("%d", &startX);
        printf("Digite a coluna inicial (0 a %d): ", TAM - 1);
        scanf("%d", &startY);

        if (startX < 0 || startX >= TAM || startY < 0 || startY >= TAM) {
            printf("Posição invalida!\n");
            return 1;
        }
        if (matriz[startX][startY] != '.') {
            printf("O ponto inicial ja esta ocupado!\n");
            return 1;
        }
    } else {
        printf("Opcao de início inválida.\n");
        return 1;
    }

    // Obstáculos (Locais que não podem ser visitados)
    int n_obstaculos;
    printf("\nQuantos obstaculos quer?\n> ");
    scanf("%d", &n_obstaculos);

    for (int i = 0; i < n_obstaculos; i++) {
    int ox, oy;
    printf("Obstaculo %d - Linha 0 a %d: ", i+1, TAM - 1);
    scanf("%d", &ox);
    printf("Obstaculo %d - Coluna 0 a %d: ", i+1, TAM - 1);
    scanf("%d", &oy);

    if (ox >= 0 && ox < TAM && oy >= 0 && oy < TAM) {
        matriz[ox][oy] = '#';
    }
    }

    // Executa o algoritmo escolhido com as coordenadas iniciais informadas
    if (opcaoBusca == 1) {
        bfs(matriz, startX, startY);
        printf("\nResultado da BFS:\n");
        imprimirMatriz(matriz);
    } else {
        dfs(matriz, startX, startY);
        printf("\nResultado da DFS:\n");
        imprimirMatriz(matriz);
    }

    return 0;
}
