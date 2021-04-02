#ifndef COMPRA_H_INCLUDED
#define COMPRA_H_INCLUDED

#include "carrinho_tad.h"

/*
Abre o arquivo dos produtos, verifica se há produtos cadastrados e chama a função desejada.
    Parametro 1 = Venda
    Parametro 2 = Compra
*/
void compraEvenda(int);

/*
Menu/Area de Venda. Inicializa uma lista (carrinho de compras), chama as funções de autenticação (Vendedor e cliente) e, em loop, chama as funções de manipulação do carrinho.
    Parâmetros: Arquivo dos Produtos;
*/
void areaVenda(FILE *);

/*
Menu/Area de Venda. Inicializa uma lista (carrinho de compras), chama a função de autenticação do fornecedor e, em loop, chama as funções de manipulação do carrinho.
    Parâmetros: Arquivo dos Produtos;
*/
void areaCompra(FILE *);

/*
Valida e retorna o id do fornecedor desejado.
*/
int selecionaFornecedor(FILE *, unsigned long *);

/*
Valida e retorna o id do vendedor, realiza uma autenticação utilizando o 'password' do mesmo.*/
int selecionaVendedor(FILE *, unsigned long *);

/*
Valida e retorna o id do cliente desejado.
*/
int selecionaCliente(FILE *, unsigned long *);

/*
Função responsável por adicionar um Produto (ou item) ao carrinho.
    Recebe e valida o id e a quantidade, impede que produtos repetidos sejam adicionados ao carrinho e verifica o estoque caso operação = Venda.
*/
void adicionarItem(FILE *, lista, int);

/*
Entrada e validação da quantidade.
*/
void entradaQuantidade(int *);

/*
Monta uma struct TItem com os dados recebidos por parâmetro e a insere no fim do carrinho de compras.
*/
void adicionarAoCarrinho(FILE *, lista, unsigned long, int);

/*
Remove um produto (item) do carrinho utilizando o seu ID.
*/
void removerItem(FILE *, lista);

/*
Lista os dados de todos os Produtos(itens) do carrinho.
*/
void listarCarrinho(FILE *,lista);

/*
Imprime na tela os dados do item armazenado no Nodo recebido.
*/
void printaItem(FILE *,TNodo *);

/*
Realiza as operações necessárias para a finalização da Venda.
    Confirmação, confirmação/entrada da data, atualização do estoque, geração da Nota Fiscal e seus respectivos Itens Nota Fiscal.
    Retorno: 1 caso falhe/cancele, 0 caso a finalização ocorra sem erros.
*/
int finalizarCarrinhoVenda(FILE *, lista, unsigned long, unsigned long);

/*
Realiza as operações necessárias para a finalização da Compra.
    Confirmação, confirmação/entrada da data, atualização do estoque, geração da Nota Compra e seus respectivos Itens Nota Compra.
    Retorno: 1 caso falhe/cancele, 0 caso a finalização ocorra sem erros.
*/
int finalizarCarrinhoCompra(FILE *, lista, unsigned long);

#endif /*COMPRA_H_INCLUDED*/
