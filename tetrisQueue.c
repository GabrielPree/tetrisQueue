#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura da peça
typedef struct {
    char tipo[5];
    int id;
} Peca;

// Definição do tamanho da fila
#define MAX 5

// Variável global para controlar o próximo ID da peça
int proximoId = 0;

// Estrutura da fila de peças
typedef struct {
    Peca pecas[MAX];
    int inicio;
    int fim;
    int total;
} fila;

// Inicia a fila de peças
void inicializarFila(fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se a fila está vazia
int filaVazia(fila *f) {
    return f->total == 0;
}

// Verifica se a fila está cheia
int filaCheia(fila *f) {
    return f->total == MAX;
}

// Adiciona um elemento na fila
void inserirPeca(fila *f, Peca p) {
    f->pecas[f->fim] = p; // Insere no final
    f->fim = (f->fim + 1) % MAX; // Lógica circular
    f->total++; // Incrementa a contagem de peças
}

// joga a primeira peça da fila removendo ela inicio
void jogarPeca(fila *f, Peca *p) {
       *p = f->pecas[f->inicio]; // Armazena o item a ser removido
    f->inicio = (f->inicio + 1) % MAX; // Atualiza o indice de inicio
    f->total--; // Diminui o total
    printf("Peça jogada: [%s, %d]\n", p->tipo, p->id);
}

// Gera uma peça com letra aleatória
Peca gerarPeca() {
    Peca novaPeca;
    
    // Escolhe uma letra aleatória entre I, O, T, L
    int numeroAleatorio = rand() % 4;  // Gera 0, 1, 2 ou 3
    
    if (numeroAleatorio == 0) {
        novaPeca.tipo[0] = 'I';
    }
    else if (numeroAleatorio == 1) {
        novaPeca.tipo[0] = 'O';
    }
    else if (numeroAleatorio == 2) {
        novaPeca.tipo[0] = 'T';
    }
    else {
        novaPeca.tipo[0] = 'L';
    }
    
    novaPeca.tipo[1] = '\0';  // Finaliza a string
    
    // ID sempre incrementado
    novaPeca.id = proximoId;
    proximoId++;
    
    return novaPeca;
}

// Gera as primeiras 5 peças automaticamente
void gerarPrimeirasPecas(fila *f) {
    for (int i = 0; i < MAX; i++) {
        Peca novaPeca = gerarPeca();
        inserirPeca(f, novaPeca);
    }
}

// Imprime as peças da fila
void mostrarFila(fila *f) {
    if (filaVazia(f)){
        printf("Fila vazia! Sem peças para mostrar.\n");
        return;
    }
    printf("Peças na fila: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) { // i= tamanho total da fila e idx = indice da fila
        printf("[%s, %d] ", f->pecas[idx].tipo, f->pecas[idx].id); // Imprime o tipo e o id
    }
    printf("\n");
}

// --- Limpa o buffer do teclado ---
void limpaBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Menu de opções
void exibirMenu(fila *f) {
    int opcao;

    printf("============================\n");
    printf("======= TETRIS QUEUE =======\n");
    printf("============================\n");
    printf("\nPeças iniciais: \n");
    mostrarFila(f);
    do {
        printf("\nMenu de Opções\n");
        printf("1. Jogar Peça (remover)\n");
        printf("2. Inserir Nova Peça (adcionar)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        printf("\n");
        limpaBufferEntrada();

        switch (opcao) {
        case 1:{
            if (filaVazia(f)){
                printf("Fila vazia! Não é possivel jogar peça.\n");
                continue; // Continua para o menu
            }
            Peca jogada;
            jogarPeca(f, &jogada);
            mostrarFila(f);
            printf("Pressione Enter para continuar...");
            getchar();
            printf("\n");
            break;
        }
        case 2: {
            if (filaCheia(f)){ // Impede inserção se estiver cheia
                printf("Fila cheia! Não é possivel inserir nova peça.\n");
                continue;
            }
            Peca novaPeca = gerarPeca();
            inserirPeca(f, novaPeca);
            printf("Peça adicionada: [%s %d]\n", novaPeca.tipo, novaPeca.id);
            mostrarFila(f);
            printf("Pressione Enter para continuar...");
            getchar();
            printf("\n");
            break;
        }
        case 0:
            printf("Saindo...\n");
            break;
        
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

int main() {
    fila f;
    Peca p;
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    inicializarFila(&f);
    gerarPrimeirasPecas(&f);
    exibirMenu(&f);
    return 0;
}