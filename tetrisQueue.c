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

// Estrutura da pilha
typedef struct {
    Peca pecas[MAX];
    int topo;
} pilha;

// --- Funções da fila ---
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
    if (filaCheia(f)){ // Impede inserção se estiver cheia
    return;
    }
    f->pecas[f->fim] = p; // Insere no final
    f->fim = (f->fim + 1) % MAX; // Lógica circular
    f->total++; // Incrementa a contagem de peças
}

// joga a primeira peça da fila removendo ela inicio
void jogarPeca(fila *f, Peca *p) {
    if (filaVazia(f)){
        return; // evita executar caso vazia
    }
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
    printf("Peças na fila (inicio -> fim): ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) { // i= tamanho total da fila e idx = indice da fila
        printf("[%s, %d] ", f->pecas[idx].tipo, f->pecas[idx].id); // Imprime o tipo e o id
    }
    printf("\n");
}

// Limpa o buffer do teclado 
void limpaBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ========================== FUNÇÕES DA PILHA ==========================

// Inicializa a pilha
void inicializarPilha(pilha *p) {
    p->topo = -1;
}

// Verifica se a pilha está vazia
int pilhaVazia(pilha *p) {
    return p->topo == -1;
}

// Verifica se a pilha está cheia
int pilhaCheia(pilha *p) {
    return p->topo == MAX - 1;
}

void push(pilha *p, Peca peca) {
    p->topo++; // Avança o topo
    p->pecas[p->topo] = peca; // Insere o novo elemento
}

// Adiciona um elemento na pilha que vem do inicio da fila
void inserirPecaPilha(fila *f, pilha *p, Peca *peca) {
    if (filaVazia(f)) {
        printf("Fila vazia! Não é possível reservar peça.\n");
        return;
    }
    if (pilhaCheia(p)) { 
        printf("Pilha cheia! Não é possível reservar mais peças.\n");
        return;
    }
    *peca = f->pecas[f->inicio]; // Armazena o item a ser removido
    f->inicio = (f->inicio + 1) % MAX; // Atualiza o indice de inicio
    f->total--; // Diminui o total
    push(p, *peca); // Insere na pilha
    printf("Peça reservada: [%s, %d]\n", peca->tipo, peca->id);

    // Gerar nova peça para repor na fila
    Peca novaPeca = gerarPeca();
    inserirPeca(f, novaPeca);
    printf("Proxima peça a chegar na fila: [%s, %d]\n", novaPeca.tipo, novaPeca.id);
}

// Remove um elemento da pilha
void pop(pilha *p, Peca *peca) {
    if (pilhaVazia(p)){
        printf("Pilha vazia! Nao é possivel remover.\n");
        return; // evita executar caso vazia
    }
    *peca = p->pecas[p->topo]; // Armazena o item a ser removido
    p->topo--; // Diminui o topo
    printf("Peça removida: [%s, %d]\n", peca->tipo, peca->id);
}

// Imprime os elementos da pilha
void mostrarPilha(pilha *p) {
    if (pilhaVazia(p)){
        printf("Pilha vazia! Nenhuma peça inserida.\n");
        return;
    }
    printf("Pilha de Peças (topo -> base): ");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%s, %d] ", p->pecas[i].tipo, p->pecas[i].id);
    }
    printf("\n");
}

// --- Troca entre peças da pilha e da fila ---

// Troca entre a primeira peça da fila com a ultima da pilha
// Troca o primeiro elemento da fila com o topo da pilha
void trocarFila(fila *f, pilha *p) {
    if (filaVazia(f)) {
        printf("Fila vazia! Não é possível trocar.\n");
        return;
    }
    if (pilhaVazia(p)) {
        printf("Pilha vazia! Não é possível trocar.\n");
        return;
    }
    
    // Armazena o item a ser trocado
    Peca tempFila = f->pecas[f->inicio];
    Peca tempPilha = p->pecas[p->topo];
    
    // Troca as peças
    f->pecas[f->inicio] = tempPilha;
    p->pecas[p->topo] = tempFila;
    
    
    printf("Troca realizada: [%s, %d] (fila) <-> [%s, %d] (pilha)\n", 
           tempFila.tipo, tempFila.id, tempPilha.tipo, tempPilha.id);
}

// Troca os 3 primeiros elementos da fila com a pilha
void trocarTresFila(fila *f, pilha *p) {
    if (f->total < 3) {
        printf("Fila não tem 3 peças! Não é possível trocar.\n");
        return;
    }
    if (p->topo < 2) { // Precisa ter pelo menos 3 elementos na pilha (índices 0,1,2)
        printf("Pilha não tem 3 peças! Não é possível trocar.\n");
        return;
    }
    
    printf("Trocando 3 peças:\n");
    
    // Troca as 3 peças
    for (int i = 0; i < 3; i++) {
        // Armazena o item a ser trocado
        int indiceFila = (f->inicio + i) % MAX;
        int indicePilha = p->topo - i; // Do topo para baixo
        
        // Troca as peças
        Peca temp = f->pecas[indiceFila];
        f->pecas[indiceFila] = p->pecas[indicePilha];
        p->pecas[indicePilha] = temp;
        
        // Imprime a troca
        printf("[%s, %d] (fila) <-> [%s, %d] (pilha)\n", 
               temp.tipo, temp.id, p->pecas[indicePilha].tipo, p->pecas[indicePilha].id);
    }
}

// Menu de opções
void exibirMenu(fila *f, pilha *p) {
    int opcao;

    printf("============================\n");
    printf("======= TETRIS QUEUE =======\n");
    printf("============================\n");
    printf("\nPeças iniciais: \n");
    mostrarFila(f);
    do {
        printf("\nMenu de Opções\n");
        printf("1. Jogar peça da frente da fila\n");
        printf("2. Enviar peça da fila para a pilha de reserva\n");
        printf("3. Usar peça da pilha de reserva\n");
        printf("4. Trocar peça da frente da fila com o topo da pilha\n");
        printf("5. Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("6. Mostrar fila e pilha\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        printf("\n");
        limpaBufferEntrada();

        switch (opcao) {
        case 1:{
            // joga uma peça
            Peca jogada;
            jogarPeca(f, &jogada);
            // insere uma nova peça na fila
            Peca novaPeca = gerarPeca();
            inserirPeca(f, novaPeca);
            printf("Proxima peça a chegar na fila: [%s, %d]\n", novaPeca.tipo, novaPeca.id);

            mostrarFila(f);
            mostrarPilha(p);
            printf("\n");
            printf("Pressione Enter para continuar...");
            getchar();
            printf("\n");
            break;
        }
        case 2: {
            // insere uma peça na pilha que vem do inicio da fila
            Peca pecaPilha;
            inserirPecaPilha(f, p, &pecaPilha);
            if (pilhaCheia(p)){
                mostrarFila(f);
                mostrarPilha(p);
                printf("\n");
                printf("Pressione Enter para continuar...");
                getchar();
                printf("\n");
                continue;
            }
            mostrarFila(f);
            mostrarPilha(p);
            printf("\n");
            printf("Pressione Enter para continuar...");
            getchar();
            printf("\n");
            break;
        }
        case 3: {
            // remove uma peça da pilha LIFO
            Peca pecaRemovida;
            pop(p, &pecaRemovida);
            mostrarFila(f);
            mostrarPilha(p);
            printf("\n");
            printf("Pressione Enter para continuar...");
            getchar();
            printf("\n");
            break;
        }
        case 4: { 
            trocarFila(f, p);
            mostrarFila(f);
            mostrarPilha(p);
            printf("\n");
            printf("Pressione Enter para continuar...");
            getchar();
            printf("\n");
            break;
        }
        case 5: {  
            trocarTresFila(f, p);
            mostrarFila(f);
            mostrarPilha(p);
            printf("\n");
            printf("Pressione Enter para continuar...");
            getchar();
            printf("\n");
            break;
        }
        case 6: {
            mostrarFila(f);
            mostrarPilha(p);
            printf("\n");
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
    pilha p;
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    inicializarFila(&f);
    inicializarPilha(&p);
    gerarPrimeirasPecas(&f);
    exibirMenu(&f, &p);
    return 0;
}