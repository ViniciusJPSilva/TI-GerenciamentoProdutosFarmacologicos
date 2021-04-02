#ifndef COMPRA_H_INCLUDED
#define COMPRA_H_INCLUDED

#include "carrinho_tad.h"

/*
Abre o arquivo dos produtos, verifica se h� produtos cadastrados e chama a fun��o desejada.
    Parametro 1 = Venda
    Parametro 2 = Compra
*/
void compraEvenda(int);

/*
Menu/Area de Venda. Inicializa uma lista (carrinho de compras), chama as fun��es de autentica��o (Vendedor e cliente) e, em loop, chama as fun��es de manipula��o do carrinho.
    Par�metros: Arquivo dos Produtos;
*/
void areaVenda(FILE *);

/*
Menu/Area de Venda. Inicializa uma lista (carrinho de compras), chama a fun��o de autentica��o do fornecedor e, em loop, chama as fun��es de manipula��o do carrinho.
    Par�metros: Arquivo dos Produtos;
*/
void areaCompra(FILE *);

/*
Valida e retorna o id do fornecedor desejado.
*/
int selecionaFornecedor(FILE *, unsigned long *);

/*
Valida e retorna o id do vendedor, realiza uma autentica��o utilizando o 'password' do mesmo.*/
int selecionaVendedor(FILE *, unsigned long *);

/*
Valida e retorna o id do cliente desejado.
*/
int selecionaCliente(FILE *, unsigned long *);

/*
Fun��o respons�vel por adicionar um Produto (ou item) ao carrinho.
    Recebe e valida o id e a quantidade, impede que produtos repetidos sejam adicionados ao carrinho e verifica o estoque caso opera��o = Venda.
*/
void adicionarItem(FILE *, lista, int);

/*
Entrada e valida��o da quantidade.
*/
void entradaQuantidade(int *);

/*
Monta uma struct TItem com os dados recebidos por par�metro e a insere no fim do carrinho de compras.
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
Realiza as opera��es necess�rias para a finaliza��o da Venda.
    Confirma��o, confirma��o/entrada da data, atualiza��o do estoque, gera��o da Nota Fiscal e seus respectivos Itens Nota Fiscal.
    Retorno: 1 caso falhe/cancele, 0 caso a finaliza��o ocorra sem erros.
*/
int finalizarCarrinhoVenda(FILE *, lista, unsigned long, unsigned long);

/*
Realiza as opera��es necess�rias para a finaliza��o da Compra.
    Confirma��o, confirma��o/entrada da data, atualiza��o do estoque, gera��o da Nota Compra e seus respectivos Itens Nota Compra.
    Retorno: 1 caso falhe/cancele, 0 caso a finaliza��o ocorra sem erros.
*/
int finalizarCarrinhoCompra(FILE *, lista, unsigned long);

#endif /*COMPRA_H_INCLUDED*/
