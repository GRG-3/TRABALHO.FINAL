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

