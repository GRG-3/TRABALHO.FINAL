#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição de estrutura para representar um livro
typedef struct {
    char nome[100];
    char autor[100];
    int quantidade;
} Livro;

// Estrutura para representar uma lista de livro
typedef struct {
    Livro *livros;
    int tamanho;
} ListaLivros;

// Função para criar uma lista de livros vazia.
ListaLivros criarLista() {
    ListaLivros lista;
    lista.livros = NULL;
    lista.tamanho = 0;
    return lista;
}

    // Função para adicionar um livro à lista
    void adicionarLivro(ListaLivros *lista, char nome[], char autor[], int quantidade) {
    lista->tamanho++;
    lista->livros = realloc(lista->livros, lista->tamanho * sizeof(Livro));
    Livro livro;
    // Copia os dados fornecidos para o livro temporario
    strcpy(livro.nome, nome);
    strcpy(livro.autor, autor);
    livro.quantidade = quantidade;
    // Adiciona o livro à lista
    lista->livros[lista->tamanho - 1] = livro;
    printf("\n\nLivro adicionado com sucesso.\n\n");
}

    // Funçao para exibir os livros de uma lista
    void exibirLivros(ListaLivros lista, const char *titulo) {
    // Verifica se a lista está vazia
    if (lista.tamanho == 0) {
        printf("\nVoce nao tem livros adicionados.\n\n");
        return;
    }
    // Exibe o nome da lista
    printf("\n%s:\n", titulo);
    for (int i = 0; i < lista.tamanho; i++) {
        printf("Livro %d:\n", i + 1);
        printf("Nome: %s\n", lista.livros[i].nome);
        printf("Autor: %s\n", lista.livros[i].autor);
        printf("Quantidade: %d\n", lista.livros[i].quantidade);
    }
    printf("\n\n");
}

    // Funçao para adicionar um livro a partir da estrada do usuario
    void adicionarLivroLista(ListaLivros *lista, const char *titulo) {
    char nome[100], autor[100];
    int quantidade;

    // Solicita os dados do livro
    printf("\nDigite o nome do livro para adicionar a lista de %s ('0' para voltar): ", titulo);
    scanf(" %[^\n]", nome);

    // Verifica se o usuario deseja voltar
    if (nome[0] == '0') return;

    printf("Digite o autor do livro: ");
    scanf(" %[^\n]", autor);

    printf("Digite a quantidade de livros que deseja: ");
    scanf("%d", &quantidade);

    // Chama a função para adicionar o livro à lista
    adicionarLivro(lista, nome, autor, quantidade);
}

    // Funçao para listar os livros de uma lista
    void listarLivros(ListaLivros lista) {
    // Verifica se a lista esta vazia
    if (lista.tamanho == 0) {
        printf("\nNao ha livros nesta lista.\n\n");
        return;
    }
    // Exibe os livros na lista
    printf("\nLivros na lista:\n");
    for (int i = 0; i < lista.tamanho; i++) {
        printf("%d. %s, por %s\n", i + 1, lista.livros[i].nome, lista.livros[i].autor);
    }
    printf("\n");
}
    // Funçao para apagar um livro de uma lista
    void apagarLivro(ListaLivros *lista) {
    listarLivros(*lista);
    int livroSelecionado;
    printf("Digite o numero do livro que deseja apagar ('0' para voltar): ");
    scanf("%d", &livroSelecionado);

    // Verifica se o usuario deseja voltar
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

    // Funçao para editar as informações de um livro

    void editarLivro(ListaLivros *listas) {
    printf("\nEscolha a lista (1 - Meus livros, 2 - Lista de desejos): ");
    int listaSelecionada;
    scanf("%d", &listaSelecionada);

    // Verifica se a lista escolhida é valida

    if (listaSelecionada < 1 || listaSelecionada > 2) {
        printf("\nLista invalida.\n");
        return;
    }

    // Lista os livros da lista selecionada

    listarLivros(listas[listaSelecionada - 1]);

    int livroSelecionado;
    printf("Digite o numero do livro que deseja editar ('0' para voltar): ");
    scanf("%d", &livroSelecionado);

    if (livroSelecionado == 0) return;

    if (livroSelecionado > 0 && livroSelecionado <= listas[listaSelecionada - 1].tamanho) {
        char nome[100], autor[100];
        int quantidade;

        // Solicita ao usuario as novas infos do livro
        printf("\nDigite o novo nome do livro: ");
        scanf(" %[^\n]", nome);

        printf("Digite o novo autor do livro: ");
        scanf(" %[^\n]", autor);

        printf("Digite a nova quantidade de livros que deseja: ");
        scanf("%d", &quantidade);

        strcpy(listas[listaSelecionada - 1].livros[livroSelecionado - 1].nome, nome);
        strcpy(listas[listaSelecionada - 1].livros[livroSelecionado - 1].autor, autor);
        listas[listaSelecionada - 1].livros[livroSelecionado - 1].quantidade = quantidade;

        printf("\nLivro editado com sucesso.\n\n");
    } else {
        printf("\nLivro nao encontrado.\n\n");
    }
}

    // Funçao para salvar a lista de livros em um arquivo

    void salvarLista(ListaLivros lista, const char *nomeArquivo) {
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("\nErro ao criar o arquivo.\n\n");
        return;
    }

    // Escreva as informações dos livros no arquivo

    for (int i = 0; i < lista.tamanho; i++) {
        fprintf(arquivo, "Livro %d:\n", i + 1);
        fprintf(arquivo, "Nome: %s\n", lista.livros[i].nome);
        fprintf(arquivo, "Autor: %s\n", lista.livros[i].autor);
        fprintf(arquivo, "Quantidade: %d\n\n", lista.livros[i].quantidade);
    }
    fclose(arquivo);
    printf("\nLista de livros salva no arquivo '%s'.\n\n", nomeArquivo);
}

    // Funçao de emprestar um livro da biblioteca

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
    // Funçao principal
    int main() {
    ListaLivros meusLivros = criarLista();
    ListaLivros listaDesejos = criarLista();
    ListaLivros listaBiblioteca = criarLista();

    // Livros disponiveis na biblioteca
    adicionarLivro(&listaBiblioteca, "1984", "George Orwell", 5);
    adicionarLivro(&listaBiblioteca, "Cem Anos de Solidao", "Gabriel Garcia Marquez", 8);
    adicionarLivro(&listaBiblioteca, "O Pequeno Principe", "Antoine de Saint-Exupery", 12);

    int opcao;

    do {
        // Exibe o menu de opçoes
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
        
    // Executa a opção escolhida pelos usuarios
    switch (opcao) {
            case 1:
                adicionarLivroLista(&meusLivros, "Meus livros");
                break;
            case 2:
                exibirLivros(meusLivros, "Meus livros");
                break;
            case 3:
                adicionarLivroLista(&listaDesejos, "Lista de desejos");
                break;
            case 4:
                editarLivro((ListaLivros[]){meusLivros, listaDesejos});
                break;
            case 5:
                exibirLivros(listaDesejos, "Lista de desejos");
                break;
            case 6:
                printf("\nEscolha a lista (1 - Meus livros, 2 - Lista de desejos): ");
                int listaSelecionada;
                scanf("%d", &listaSelecionada);
                if (listaSelecionada == 1) {
                    apagarLivro(&meusLivros);
                } else if (listaSelecionada == 2) {
                    apagarLivro(&listaDesejos);
                } else {
                    printf("\nLista invalida.\n");
                }
                break;
            case 7:
                emprestarLivro(&meusLivros, &listaBiblioteca);
                break;
            case 8:
                salvarLista(meusLivros, "Lista_de_livros.txt");
                break;
            case 9:
                printf("\nObrigado por utilizar o programa. Volte sempre!\n\n");
                break;
            default:
                printf("\nEssa opcao nao existe.\n");
                break;
        }   
          } while (opcao != 9);

    free(meusLivros.livros);
    free(listaDesejos.livros);
    free(listaBiblioteca.livros);

    return 0;
}
