#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void apagarLivro(ListaLivros *lista) {
    listarLivros(*lista);
    int livroSelecionado;
    printf("Digite o numero do livro que deseja apagar ('0' para voltar): ");
    scanf("%d", &livroSelecionado);

    if (livroSelecionado == 0) return;

    if (livroSelecionado > 0 && livroSelecionado <= lista->tamanho) {
        for (int i = livroSelecionado - 1; i < lista->tamanho - 1; i++) {
            lista->livros[i] = lista->livros[i + 1];
        }
        lista->tamanho--;
        lista->livros = realloc(lista->livros, lista->tamanho * sizeof(Livro));
        printf("\nLivro removido com sucesso.\n\n");
    } else {
        printf("\nLivro nao encontrado.\n\n");
    }
}

void editarLivro(ListaLivros *listas) {
    printf("\nEscolha a lista (1 - Meus livros, 2 - Lista de desejos): ");
    int listaSelecionada;
    scanf("%d", &listaSelecionada);

    if (listaSelecionada < 1 || listaSelecionada > 2) {
        printf("\nLista invalida.\n");
        return;
    }

    listarLivros(listas[listaSelecionada - 1]);

    int livroSelecionado;
    printf("Digite o numero do livro que deseja editar ('0' para voltar): ");
    scanf("%d", &livroSelecionado);

    if (livroSelecionado == 0) return;

    if (livroSelecionado > 0 && livroSelecionado <= listas[listaSelecionada - 1].tamanho) {
        char nome[100], autor[100];
        int quantidade;

        printf("\nDigite o novo nome do livro: ");
        scanf(" %[^\n]", nome);

        printf("Digite o novo autor do livro: ");
        scanf(" %[^\n]", autor);

        printf("Digite a nova quantidade de livros que possui: ");
        scanf("%d", &quantidade);

        strcpy(listas[listaSelecionada - 1].livros[livroSelecionado - 1].nome, nome);
        strcpy(listas[listaSelecionada - 1].livros[livroSelecionado - 1].autor, autor);
        listas[listaSelecionada - 1].livros[livroSelecionado - 1].quantidade = quantidade;

        printf("\nLivro editado com sucesso.\n\n");
    } else {
        printf("\nLivro nao encontrado.\n\n");
    }
}

void salvarLista(ListaLivros lista, const char *nomeArquivo) {
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("\nErro ao criar o arquivo.\n\n");
        return;
    }
    for (int i = 0; i < lista.tamanho; i++) {
        fprintf(arquivo, "Livro %d:\n", i + 1);
        fprintf(arquivo, "Nome: %s\n", lista.livros[i].nome);
        fprintf(arquivo, "Autor: %s\n", lista.livros[i].autor);
        fprintf(arquivo, "Quantidade: %d\n\n", lista.livros[i].quantidade);
    }
    fclose(arquivo);
    printf("\nLista de livros salva no arquivo '%s'.\n\n", nomeArquivo);
}

void emprestarLivro(ListaLivros *lista, ListaLivros *listaBiblioteca) {
    printf("\nLivros disponiveis para emprestimo:\n");
    for (int i = 0; i < listaBiblioteca->tamanho; i++) {
        printf("%d. %s, por %s - Disponiveis: %d\n", i + 1, listaBiblioteca->livros[i].nome,
               listaBiblioteca->livros[i].autor, listaBiblioteca->livros[i].quantidade);
    }
    int escolhaLivro;
    printf("Escolha o livro que deseja pegar emprestado ('0' para voltar): ");
    scanf("%d", &escolhaLivro);

    if (escolhaLivro == 0) return;

    if (escolhaLivro > 0 && escolhaLivro <= listaBiblioteca->tamanho) {
        char nome[100], autor[100];
        int quantidade;

        strcpy(nome, listaBiblioteca->livros[escolhaLivro - 1].nome);
        strcpy(autor, listaBiblioteca->livros[escolhaLivro - 1].autor);

        printf("Quantos livros deseja pegar emprestado? ");
        scanf("%d", &quantidade);

        if (quantidade <= listaBiblioteca->livros[escolhaLivro - 1].quantidade) {
            adicionarLivro(lista, nome, autor, quantidade);
            listaBiblioteca->livros[escolhaLivro - 1].quantidade -= quantidade;
        } else {
            printf("\nNao ha livros suficientes para emprestar.\n\n");
        }
    } else {
        printf("\nLivro nao encontrado.\n\n");
    }
}
int main() {
    ListaLivros meusLivros = criarLista();
    ListaLivros listaDesejos = criarLista();
    ListaLivros listaBiblioteca = criarLista();

    adicionarLivro(&listaBiblioteca, "1984", "George Orwell", 5);
    adicionarLivro(&listaBiblioteca, "Cem Anos de Solidao", "Gabriel Garcia Marquez", 8);
    adicionarLivro(&listaBiblioteca, "O Pequeno Principe", "Antoine de Saint-Exupery", 12);

    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar livro\n");
        printf("2. Exibir meus livros\n");
        printf("3. Adicionar livro a lista de desejos\n");
        printf("4. Editar livro\n");
        printf("5. Exibir lista de desejos\n");
        printf("6. Apagar livro\n");
        printf("7. Pegar livro emprestado\n");
        printf("8. Salvar lista de livros\n");
        printf("9. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
    }
