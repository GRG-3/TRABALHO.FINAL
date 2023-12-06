#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char autor[100];
    int quantidade;
} Livro;

typedef struct {
    Livro *livros;
    int tamanho;
} ListaLivros;

ListaLivros criarLista() {
    ListaLivros lista;
    lista.livros = NULL;
    lista.tamanho = 0;
    return lista;
}

void adicionarLivro(ListaLivros *lista, char nome[], char autor[], int quantidade) {
    lista->tamanho++;
    lista->livros = realloc(lista->livros, lista->tamanho * sizeof(Livro));
    Livro livro;
    strcpy(livro.nome, nome);
    strcpy(livro.autor, autor);
    livro.quantidade = quantidade;
    lista->livros[lista->tamanho - 1] = livro;
    printf("\n\nLivro adicionado com sucesso.\n\n");
}

void exibirLivros(ListaLivros lista, const char *titulo) {
    if (lista.tamanho == 0) {
        printf("\nVoce nao tem livros %s.\n\n", titulo);
        return;
    }
    printf("\n%s:\n", titulo);
    for (int i = 0; i < lista.tamanho; i++) {
        printf("Livro %d:\n", i + 1);
        printf("Nome: %s\n", lista.livros[i].nome);
        printf("Autor: %s\n", lista.livros[i].autor);
        printf("Quantidade: %d\n", lista.livros[i].quantidade);
    }
    printf("\n\n");
}

void adicionarLivroLista(ListaLivros *lista, const char *titulo) {
    char nome[100], autor[100];
    int quantidade;

    printf("\nDigite o nome do livro para adicionar a lista de %s ('0' para voltar): ", titulo);
    scanf(" %[^\n]", nome);

    if (nome[0] == '0') return;

    printf("Digite o autor do livro: ");
    scanf(" %[^\n]", autor);

    printf("Digite a quantidade de livros que possui: ");
    scanf("%d", &quantidade);

    adicionarLivro(lista, nome, autor, quantidade);
}

void listarLivros(ListaLivros lista) {
    if (lista.tamanho == 0) {
        printf("\nNao ha livros nesta lista.\n\n");
        return;
    }
    printf("\nLivros na lista:\n");
    for (int i = 0; i < lista.tamanho; i++) {
        printf("%d. %s, por %s\n", i + 1, lista.livros[i].nome, lista.livros[i].autor);
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
