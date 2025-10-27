#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

void inserirItemVetor(Item mochila[], int *tamanho);
void removerItemVetor(Item mochila[], int *tamanho);
void listarVetor(Item mochila[], int tamanho);
int buscarSequencialVetor(Item mochila[], int tamanho, char nome[], int *comparacoes);
void ordenarVetor(Item mochila[], int tamanho);
int buscarBinariaVetor(Item mochila[], int tamanho, char nome[], int *comparacoes);

No* inserirItemLista(No* inicio);
No* removerItemLista(No* inicio);
void listarLista(No* inicio);
int buscarSequencialLista(No* inicio, char nome[], int *comparacoes);

int main() {
    Item mochilaVetor[MAX_ITENS];
    int tamanhoVetor = 0;
    No* mochilaLista = NULL;

    int opcao, estrutura, comparacoes = 0;
    char nomeBusca[30];

    do {
        printf("\n=== SISTEMA DE MOCHILA ===\n");
        printf("Escolha a estrutura:\n");
        printf("1. Vetor (lista sequencial)\n");
        printf("2. Lista encadeada\n");
        printf("3. Sair\n");
        printf("Opcao: ");
        scanf("%d", &estrutura);
        getchar();

        if (estrutura == 3) break;

        do {
            printf("\n=== MENU ===\n");
            printf("1. Inserir item\n");
            printf("2. Remover item\n");
            printf("3. Listar itens\n");
            printf("4. Buscar item (sequencial)\n");
            if (estrutura == 1) {
                printf("5. Ordenar vetor e buscar (binaria)\n");
            }
            printf("0. Voltar\n");
            printf("Opcao: ");
            scanf("%d", &opcao);
            getchar();

            if (estrutura == 1) { // VETOR
                switch (opcao) {
                    case 1:
                        inserirItemVetor(mochilaVetor, &tamanhoVetor);
                        break;
                    case 2:
                        removerItemVetor(mochilaVetor, &tamanhoVetor);
                        break;
                    case 3:
                        listarVetor(mochilaVetor, tamanhoVetor);
                        break;
                    case 4:
                        printf("Nome do item a buscar: ");
                        fgets(nomeBusca, sizeof(nomeBusca), stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        comparacoes = 0;
                        if (buscarSequencialVetor(mochilaVetor, tamanhoVetor, nomeBusca, &comparacoes) == -1)
                            printf("Item nao encontrado.\n");
                        printf("Comparacoes feitas: %d\n", comparacoes);
                        break;
                    case 5:
                        ordenarVetor(mochilaVetor, tamanhoVetor);
                        printf("Nome do item a buscar (binaria): ");
                        fgets(nomeBusca, sizeof(nomeBusca), stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        comparacoes = 0;
                        if (buscarBinariaVetor(mochilaVetor, tamanhoVetor, nomeBusca, &comparacoes) == -1)
                            printf("Item nao encontrado.\n");
                        printf("Comparacoes feitas (busca binaria): %d\n", comparacoes);
                        break;
                }
            } 
            else if (estrutura == 2) { // LISTA
                switch (opcao) {
                    case 1:
                        mochilaLista = inserirItemLista(mochilaLista);
                        break;
                    case 2:
                        mochilaLista = removerItemLista(mochilaLista);
                        break;
                    case 3:
                        listarLista(mochilaLista);
                        break;
                    case 4:
                        printf("Nome do item a buscar: ");
                        fgets(nomeBusca, sizeof(nomeBusca), stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        comparacoes = 0;
                        if (buscarSequencialLista(mochilaLista, nomeBusca, &comparacoes) == -1)
                            printf("Item nao encontrado.\n");
                        printf("Comparacoes feitas: %d\n", comparacoes);
                        break;
                }
            }

        } while (opcao != 0);

    } while (estrutura != 3);

    printf("\nEncerrando o sistema...\n");
    return 0;
}

void inserirItemVetor(Item mochila[], int *tamanho) {
    if (*tamanho >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*tamanho] = novo;
    (*tamanho)++;
    printf("Item inserido com sucesso!\n");
}

void removerItemVetor(Item mochila[], int *tamanho) {
    if (*tamanho == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int i, encontrado = 0;
    for (i = 0; i < *tamanho; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado.\n");
        return;
    }

    for (int j = i; j < *tamanho - 1; j++)
        mochila[j] = mochila[j + 1];

    (*tamanho)--;
    printf("Item removido com sucesso.\n");
}

void listarVetor(Item mochila[], int tamanho) {
    if (tamanho == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    printf("\nItens na mochila:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d) %s | %s | %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

int buscarSequencialVetor(Item mochila[], int tamanho, char nome[], int *comparacoes) {
    for (int i = 0; i < tamanho; i++) {
        (*comparacoes)++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado: %s (%s), qtd: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return i;
        }
    }
    return -1;
}

void ordenarVetor(Item mochila[], int tamanho) {
    Item temp;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (strcmp(mochila[i].nome, mochila[j].nome) > 0) {
                temp = mochila[i];
                mochila[i] = mochila[j];
                mochila[j] = temp;
            }
        }
    }
    printf("Itens ordenados por nome.\n");
}

int buscarBinariaVetor(Item mochila[], int tamanho, char nome[], int *comparacoes) {
    int inicio = 0, fim = tamanho - 1, meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            printf("Item encontrado: %s (%s), qtd: %d\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

No* inserirItemLista(No* inicio) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("Erro de memoria.\n");
        return inicio;
    }

    printf("Nome: ");
    fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = inicio;
    printf("Item inserido na lista.\n");
    return novo;
}

No* removerItemLista(No* inicio) {
    if (!inicio) {
        printf("Lista vazia.\n");
        return NULL;
    }

    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = inicio, *anterior = NULL;

    while (atual && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!atual) {
        printf("Item nao encontrado.\n");
        return inicio;
    }

    if (!anterior) inicio = atual->proximo;
    else anterior->proximo = atual->proximo;

    free(atual);
    printf("Item removido com sucesso.\n");
    return inicio;
}

void listarLista(No* inicio) {
    if (!inicio) {
        printf("Lista vazia.\n");
        return;
    }

    No* p = inicio;
    printf("\nItens na lista:\n");
    while (p) {
        printf("- %s | %s | %d\n", p->dados.nome, p->dados.tipo, p->dados.quantidade);
        p = p->proximo;
    }
}

int buscarSequencialLista(No* inicio, char nome[], int *comparacoes) {
    No* p = inicio;
    while (p) {
        (*comparacoes)++;
        if (strcmp(p->dados.nome, nome) == 0) {
            printf("Item encontrado: %s (%s), qtd: %d\n", p->dados.nome, p->dados.tipo, p->dados.quantidade);
            return 1;
        }
        p = p->proximo;
    }
    return -1;
}
