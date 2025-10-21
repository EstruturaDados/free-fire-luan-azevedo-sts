#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Definição da capacidade máxima da mochila
#define MAX_ITENS 10
#define MAX_NOME 50
#define MAX_TIPO 30

// 🎯 Estrutura para representar um Item (Nível Novato)
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

// Variáveis globais para o inventário
Item mochila[MAX_ITENS];
int numItens = 0; // Contador de itens atuais na mochila

// ⚙️ Função para limpar a tela
void limparTela() {
    // Simula a limpeza da tela (compatível com a maioria dos terminais)
    #ifdef _WIN32
        system("cls");
    #else
        // Para sistemas baseados em Unix (Linux, macOS)
        printf("\033[H\033[J"); 
    #endif
}

// ⚙️ Função para exibir o menu
void exibirMenu() {
    printf("\n============================================\n");
    printf("     Desafio Codigo da Ilha - Novato    \n");
    printf("============================================\n");
    printf("        Itens na Mochila: %d/%d\n", numItens, MAX_ITENS);
    printf("--------------------------------------------\n");
    printf(" 1. Adicionar Item\n");
    printf(" 2. Remover Item pelo Nome\n");
    printf(" 3. Listar Itens Cadastrados\n");
    printf(" 0. Sair e Escapar da Ilha\n");
    printf("--------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

// ⚙️ Função para adicionar um novo item (Funcionalidade 1)
void adicionarItem() {
    if (numItens >= MAX_ITENS) {
        printf("\n🛑 Mochila Cheia! Nao ha mais espaco para itens.\n");
        return;
    }

    Item novoItem;
    printf("\n--- Adicionar Novo Item ---\n");

    // Leitura do Nome
    printf("Nome do Item (max %d caracteres): ", MAX_NOME - 1);
    scanf(" %49[^\n]", novoItem.nome); // Lê a linha, limitado a 49 caracteres

    // Leitura do Tipo
    printf("Tipo do Item (ex: Arma, Curativo, Munição, max %d caracteres): ", MAX_TIPO - 1);
    scanf(" %29[^\n]", novoItem.tipo);

    // Leitura da Quantidade
    printf("Quantidade: ");
    while (scanf("%d", &novoItem.quantidade) != 1 || novoItem.quantidade <= 0) {
        printf("Quantidade invalida. Digite um numero inteiro positivo: ");
        // Limpa o buffer de entrada para evitar loop infinito
        while (getchar() != '\n');
    }
    // Limpa o buffer de entrada
    while (getchar() != '\n'); 

    // Adiciona o item ao vetor
    mochila[numItens] = novoItem;
    numItens++;

    printf("\n✅ Item '%s' adicionado com sucesso!\n", novoItem.nome);
}

// ⚙️ Função para remover um item (Funcionalidade 2)
void removerItem() {
    if (numItens == 0) {
        printf("\n🛑 Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeRemover[MAX_NOME];
    printf("\n--- Remover Item ---\n");
    printf("Digite o nome exato do item para remover: ");
    scanf(" %49[^\n]", nomeRemover);

    int indiceEncontrado = -1;
    // Busca linear (simples) para encontrar o item
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado != -1) {
        // Item encontrado, realiza a remoção (desloca os itens posteriores)
        for (int i = indiceEncontrado; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        numItens--;
        printf("\n✅ Item '%s' removido com sucesso!\n", nomeRemover);
    } else {
        printf("\n❌ Item '%s' nao encontrado na mochila.\n", nomeRemover);
    }
}

// ⚙️ Função para listar todos os itens (Funcionalidade 3)
void listarItens() {
    if (numItens == 0) {
        printf("\n🛑 Mochila vazia! Nao ha itens para listar.\n");
        return;
    }

    printf("\n======================================================\n");
    printf("              Inventario Atual da Mochila             \n");
    printf("======================================================\n");
    printf("  # | Nome (%.*s) | Tipo (%.*s) | Quantidade \n", 
           MAX_NOME - 10, "Nome", MAX_TIPO - 10, "Tipo"); // Ajuste de largura para tabela
    printf("------------------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf(" %2d | %-20s | %-15s | %10d \n", 
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("------------------------------------------------------\n");
    printf("Total de itens distintos: %d\n", numItens);
}


// 🎮 Função Principal (Menu Interativo com do-while e switch)
int main() {
    int opcao;
    
    // Configura a leitura para evitar problemas com caracteres acentuados no printf/scanf em alguns ambientes
    // setlocale(LC_ALL, "Portuguese"); // Opcional, dependendo do compilador/OS

    do {
        limparTela();
        exibirMenu();
        
        // Verifica se a entrada é um inteiro válido
        if (scanf("%d", &opcao) != 1) {
            // Se a leitura falhar (não for um número)
            opcao = -1; // Define uma opção inválida
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }
        // Limpa o buffer de entrada para a próxima leitura de scanf (necessário após scanf("%d"))
        while (getchar() != '\n'); 

        switch (opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 0:
                printf("\n Adeus! Plano de Fuga Iniciado. Boa Sorte!\n");
                break;
            default:
                printf("\n Opcao invalida. Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); // Espera o usuário pressionar Enter
        }

    } while (opcao != 0);

    return 0;
}