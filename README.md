Visão geral

O nosso projeto é um programa C que facilita o gerenciamento de listas de livros. Ele permite aos usuários criar, editar, excluir e exibir listas de livros. Além disso, os usuários podem pegar livros emprestados de uma biblioteca e salvar suas listas de livros em um arquivo.

Características

Criar listas: O programa permite aos usuários criar listas diferentes para seus livros.

Adicionar livro: Os usuários podem adicionar um livro à sua lista, especificando o nome, autor e quantidade.

Exibir livros: Visualize os livros em uma lista, mostrando detalhes como nome, autor e quantidade.

Excluir livro: Remove um livro da lista.

Editar livro: Modifique os detalhes de um livro na lista.

Salvar lista em arquivo: Salva a lista de livros em um arquivo especificado.

Emprestar Livro da Biblioteca: Emprestar livros de uma biblioteca, atualizando a lista de usuários e reduzindo a quantidade disponível da biblioteca.

Para usar o programa, siga estas etapas:

1. Compile o programa usando um compilador C (por exemplo, gcc LivroLista.c -o LivroLista).
2. Execute o executável ( ./LivroLista).
3. Siga as instruções na tela para interagir com o programa.

Exemplos de uso

Adicionando um livro:
Para adicionar um livro à sua lista, selecione a opção “Adicionar livro”, insira os dados do livro (nome, autor, quantidade) e o livro será adicionado.

Editando um livro:
Escolha a opção “Editar livro”, selecione o livro a ser editado, forneça novos detalhes e o livro será atualizado.

Excluindo um livro:
Selecione a opção “Apagar livro”, escolha o livro que deseja excluir e o livro será removido da sua lista.

Emprestando um livro da biblioteca:
Escolha a opção “Pegar livro emprestado”, selecione um livro da biblioteca, especifique a quantidade a emprestar e o livro será adicionado à sua lista.

Salvando lista em arquivo:
Selecione a opção "Salvar lista de livros", digite um nome de arquivo e sua lista será salva no arquivo especificado.

*Considerações finais*

O programa usa alocação dinâmica de memória para gerenciar a lista de livros.
A validação de entrada não é implementada extensivamente, portanto espera-se que os usuários forneçam entradas válidas.
