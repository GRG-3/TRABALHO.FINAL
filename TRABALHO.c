#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um livro
struct Livro {
    char nome[50];
    int quantidade;
};

// Funcao para adicionar um livro na lista
void adicionarLivro(struct Livro lista[], int *quantidadeLivros) {
    printf("Digite o nome do Livro: ");
    getchar(); 
    fgets(lista[*quantidadeLivros].nome, sizeof(lista[*quantidadeLivros].nome), stdin);
    lista[*quantidadeLivros].nome[strcspn(lista[*quantidadeLivros].nome, "\n")] = '\0';

    printf("Digite a quantidade do Livro: ");
    char quantidadeStr[10]; // String temporária para armazenar a quantidade
    fgets(quantidadeStr, sizeof(quantidadeStr), stdin);
    sscanf(quantidadeStr, "%d", &lista[*quantidadeLivros].quantidade);

    (*quantidadeLivros)++;
}




// Funcao para exibir a lista de livros
void exibirLista(struct Livro lista[], int quantidadeLivros) {
    printf("\nLista de Livros:\n");
    for (int i = 0; i < quantidadeLivros; i++) {
        printf("Nome: %s, Quantidade: %d\n",
               lista[i].nome, lista[i].quantidade);
    }
    printf("\n");
}

// Funcao para buscar um livro na lista
void buscarLivro(struct Livro lista[], int quantidadeLivros) {
    char nomeBusca[50];
    getchar();
    printf("Digite o nome do Livro a ser buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < quantidadeLivros; i++) {
        if (strcmp(lista[i].nome, nomeBusca) == 0) {
            printf("Livro encontrado:\n");
            printf("Nome: %s, Quantidade: %d\n",
                   lista[i].nome, lista[i].quantidade);
            return;
        }
    }

    printf("Livro nao encontrado.\n");
}

// Funcao para editar a quantidade de um livro na lista
void editarLivro(struct Livro lista[], int quantidadeLivros) {
    char nomeEdicao[50];
    getchar();
    printf("Digite o nome do Livro a ser editado: ");
    fgets(nomeEdicao, sizeof(nomeEdicao), stdin);
    nomeEdicao[strcspn(nomeEdicao, "\n")] = '\0';

    for (int i = 0; i < quantidadeLivros; i++) {
        if (strcmp(lista[i].nome, nomeEdicao) == 0) {
            printf("Digite a nova quantidade do Livro: ");
            scanf("%d", &lista[i].quantidade);
            getchar();

            printf("Livro editado com sucesso.\n");
            return;
        }
    }

    printf("Livro nao encontrado.\n");
}

// Funcao para remover um livro da lista
void removerLivro(struct Livro lista[], int *quantidadeLivros) {
    char nomeRemocao[50];
    getchar();
    printf("Digite o nome do Livro a ser removido: ");
    fgets(nomeRemocao, sizeof(nomeRemocao), stdin);
    nomeRemocao[strcspn(nomeRemocao, "\n")] = '\0';

    for (int i = 0; i < *quantidadeLivros; i++) {
        if (strcmp(lista[i].nome, nomeRemocao) == 0) {
            lista[i] = lista[(*quantidadeLivros) - 1];
            (*quantidadeLivros)--;
            printf("Livro removido com sucesso.\n");
            return;
        }
    }

    printf("Livro nao encontrado.\n");
}

// Funcao para emprestar um livro da lista de livros disponiveis
void emprestarLivro(struct Livro lista[], int quantidadeLivros) {
    printf("Lista de Livros disponiveis para emprestimo:\n");
    struct Livro livrosDisponiveis[10] = {
        {"Arsene Lupin, Ladrao de Casaca", 15},
        {"Dom Quixote", 8},
        {"It", 12},
        {"Diario de um Banana", 20},
        {"O Pequeno Principe", 22},
        {"Harry Potter (serie)", 4},
        {"Cinderela", 17},
        {"Ela, a Feiticeira", 9},
        {"Orgulho e Preconceito", 19},
        {"Um Conto de Duas Cidades", 32}
    };

    for (int i = 0; i < 10; i++) {
        printf("%d. %s (Quantidade Disponivel: %d)\n", i + 1, livrosDisponiveis[i].nome, livrosDisponiveis[i].quantidade);
    }

    int escolha;
    printf("Escolha o numero do Livro a ser emprestado: ");
    scanf("%d", &escolha);

    if (escolha >= 1 && escolha <= 10) {
        int indexLivro = escolha - 1;
        if (livrosDisponiveis[indexLivro].quantidade > 0) {
            int quantidadeDesejada;
            printf("Digite a quantidade desejada: ");
            scanf("%d", &quantidadeDesejada);

            if (quantidadeDesejada <= livrosDisponiveis[indexLivro].quantidade) {
                livrosDisponiveis[indexLivro].quantidade -= quantidadeDesejada;
                printf("%d unidades do Livro '%s' emprestadas com sucesso.\n", quantidadeDesejada, livrosDisponiveis[indexLivro].nome);
            } else {
                printf("Nao ha quantidade suficiente disponivel para emprestimo do Livro '%s'.\n", livrosDisponiveis[indexLivro].nome);
            }
        } else {
            printf("Nao ha copias disponiveis para emprestimo do Livro '%s'.\n", livrosDisponiveis[indexLivro].nome);
        }
    } else {
        printf("Opcao invalida.\n");
    }
}

// Funcao para salvar a lista de livros em um arquivo
void salvarLista(struct Livro lista[], int quantidadeLivros) {
    FILE *arquivo;
    arquivo = fopen("lista_Livros.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    for (int i = 0; i < quantidadeLivros; i++) {
        fprintf(arquivo, "%s %d\n", lista[i].nome, lista[i].quantidade);
    }

    fclose(arquivo);
    printf("Lista de Livros salva com sucesso.\n");
}

// Inicializar a lista de livro
struct Livro* inicializarCatalogo(int *quantidadeLivros) {
    *quantidadeLivros = 0;

    struct Livro *lista = (struct Livro*)malloc((*quantidadeLivros) * sizeof(struct Livro));
    if (lista == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    return lista;
}

// Funcao principal
int main() {
    int quantidadeLivros;
    struct Livro *lista = inicializarCatalogo(&quantidadeLivros);
    int opcao;

    do {
        // Menu de opcoes
        printf("Menu:\n");
        printf("1. Adicionar Livro\n");
        printf("2. Exibir Lista\n");
        printf("3. Buscar Livro\n");
        printf("4. Editar Livro\n");
        printf("5. Remover Livro\n");
        printf("6. Pegar Livro Emprestado\n");
        printf("7. Salvar Lista em Arquivo\n");
        printf("0. Sair\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        // Switch para escolher a acao conforme a opcao escolhida
        switch (opcao) {
            case 1:
                adicionarLivro(lista, &quantidadeLivros);
                break;
            case 2:
                exibirLista(lista, quantidadeLivros);
                break;
            case 3:
                buscarLivro(lista, quantidadeLivros);
                break;
            case 4:
                editarLivro(lista, quantidadeLivros);
                break;
            case 5:
                removerLivro(lista, &quantidadeLivros);
                break;
            case 6:
                emprestarLivro(lista, quantidadeLivros);
                break;
            case 7:
                salvarLista(lista, quantidadeLivros);
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    free(lista);

    return 0;
}
