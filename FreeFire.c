#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire

#define MAX_ITENS 10

// Definição da struct
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Vetor de itens
struct Item mochila[MAX_ITENS];
int totalItens = 0;

int main() {
    int opcao;

    do {
        printf("\n=== SISTEMA DE GERENCIAMENTO DA MOCHILA ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                // Inserir item
                if (totalItens >= MAX_ITENS) {
                    printf("A mochila esta cheia!\n");
                    break;
                }

                struct Item novo;
                printf("Digite o nome do item: ");
                scanf("%s", novo.nome);
                printf("Digite o tipo do item: ");
                scanf("%s", novo.tipo);
                printf("Digite a quantidade: ");
                scanf("%d", &novo.quantidade);

                mochila[totalItens] = novo;
                totalItens++;
                printf("Item inserido com sucesso!\n");
                break;
            }

            case 2: {
                // Remover item
                if (totalItens == 0) {
                    printf("A mochila esta vazia!\n");
                    break;
                }

                char nome[30];
                printf("Digite o nome do item a ser removido: ");
                scanf("%s", nome);

                int encontrado = 0;
                for (int i = 0; i < totalItens; i++) {
                    if (strcmp(mochila[i].nome, nome) == 0) {
                        for (int j = i; j < totalItens - 1; j++) {
                            mochila[j] = mochila[j + 1];
                        }
                        totalItens--;
                        encontrado = 1;
                        printf("Item removido com sucesso!\n");
                        break;
                    }
                }

                if (!encontrado) {
                    printf("Item nao encontrado!\n");
                }
                break;
            }

            case 3: {
                // Listar itens
                if (totalItens == 0) {
                    printf("A mochila esta vazia!\n");
                    break;
                }

                printf("\n=== ITENS DA MOCHILA ===\n");
                for (int i = 0; i < totalItens; i++) {
                    printf("Item %d: Nome: %s | Tipo: %s | Quantidade: %d\n",
                           i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                }
                printf("Total de itens: %d\n", totalItens);
                printf("=========================\n");
                break;
            }

            case 4: {
                // Buscar item
                if (totalItens == 0) {
                    printf("A mochila esta vazia!\n");
                    break;
                }

                char nome[30];
                printf("Digite o nome do item que deseja buscar: ");
                scanf("%s", nome);

                int encontrado = 0;
                for (int i = 0; i < totalItens; i++) {
                    if (strcmp(mochila[i].nome, nome) == 0) {
                        printf("Item encontrado: Nome: %s | Tipo: %s | Quantidade: %d\n",
                               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("Item nao encontrado!\n");
                }
                break;
            }

            case 0: {
                printf("Encerrando o programa...\n");
                break;
            }

            default: {
                printf("Opcao invalida! Tente novamente.\n");
                break;
            }
        }
    } while (opcao != 0);

    return 0;
}
