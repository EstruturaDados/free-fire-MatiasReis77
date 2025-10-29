#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

void cadastrarComponentes(Componente[], int*);
void mostrarComponentes(Componente[], int);
void bubbleSortNome(Componente[], int, int*);
void insertionSortTipo(Componente[], int, int*);
void selectionSortPrioridade(Componente[], int, int*);
int buscaBinariaPorNome(Componente[], int, char[], int*);
void medirTempo(void (*algoritmo)(Componente[], int, int*), Componente[], int, const char*);
void copiarVetor(Componente[], Componente[], int);

int main() {
    Componente componentes[MAX_COMPONENTES];
    Componente copia[MAX_COMPONENTES];
    int n = 0;
    int comparacoes = 0;
    char nomeBusca[30];
    int opcao;
    clock_t inicio, fim;

    do {
        printf("\n=== SISTEMA DE MONTAGEM DA TORRE DE FUGA ===\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Ordenar por NOME (Bubble Sort)\n");
        printf("3. Ordenar por TIPO (Insertion Sort)\n");
        printf("4. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5. Buscar componente-chave (após ordenação por nome)\n");
        printf("6. Mostrar componentes atuais\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarComponentes(componentes, &n);
                break;

            case 2:
                copiarVetor(copia, componentes, n);
                medirTempo(bubbleSortNome, copia, n, "Bubble Sort (por nome)");
                mostrarComponentes(copia, n);
                break;

            case 3:
                copiarVetor(copia, componentes, n);
                medirTempo(insertionSortTipo, copia, n, "Insertion Sort (por tipo)");
                mostrarComponentes(copia, n);
                break;

            case 4:
                copiarVetor(copia, componentes, n);
                medirTempo(selectionSortPrioridade, copia, n, "Selection Sort (por prioridade)");
                mostrarComponentes(copia, n);
                break;

            case 5:
                printf("Digite o nome do componente-chave: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                copiarVetor(copia, componentes, n);
                comparacoes = 0;
                bubbleSortNome(copia, n, &comparacoes); // ordena antes da busca binária
                comparacoes = 0;
                inicio = clock();
                int pos = buscaBinariaPorNome(copia, n, nomeBusca, &comparacoes);
                fim = clock();
                if (pos != -1)
                    printf("✅ Componente encontrado: %s | %s | prioridade %d\n", copia[pos].nome, copia[pos].tipo, copia[pos].prioridade);
                else
                    printf("❌ Componente não encontrado.\n");
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, (double)(fim - inicio) / CLOCKS_PER_SEC);
                break;

            case 6:
                mostrarComponentes(componentes, n);
                break;

            case 0:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}

void cadastrarComponentes(Componente v[], int *n) {
    int qtd;
    printf("Quantos componentes deseja cadastrar (max %d)? ", MAX_COMPONENTES);
    scanf("%d", &qtd);
    getchar();

    for (int i = 0; i < qtd && *n < MAX_COMPONENTES; i++) {
        printf("\nComponente %d:\n", *n + 1);
        printf("Nome: ");
        fgets(v[*n].nome, sizeof(v[*n].nome), stdin);
        v[*n].nome[strcspn(v[*n].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(v[*n].tipo, sizeof(v[*n].tipo), stdin);
        v[*n].tipo[strcspn(v[*n].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &v[*n].prioridade);
        getchar();
        (*n)++;
    }
}

void mostrarComponentes(Componente v[], int n) {
    printf("\n=== Componentes ===\n");
    for (int i = 0; i < n; i++) {
        printf("%2d. %-20s | %-15s | prioridade: %d\n", i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

void bubbleSortNome(Componente v[], int n, int *comparacoes) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void insertionSortTipo(Componente v[], int n, int *comparacoes) {
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            (*comparacoes)++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

void selectionSortPrioridade(Componente v[], int n, int *comparacoes) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].prioridade < v[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
}

int buscaBinariaPorNome(Componente v[], int n, char nome[], int *comparacoes) {
    int inicio = 0, fim = n - 1, meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(v[meio].nome, nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

void medirTempo(void (*algoritmo)(Componente[], int, int*), Componente v[], int n, const char *nomeAlgoritmo) {
    int comparacoes = 0;
    clock_t inicio = clock();
    algoritmo(v, n, &comparacoes);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\n[%s] Comparações: %d | Tempo: %.6f s\n", nomeAlgoritmo, comparacoes, tempo);
}

void copiarVetor(Componente destino[], Componente origem[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}
