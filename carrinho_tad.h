#ifndef CARRINHO_TAD_H_INCLUDED
#define CARRINHO_TAD_H_INCLUDED

typedef struct{
    unsigned long idProduto;
    int quantidade;
    float valorUnitario;
}TItem;

typedef struct Nodo{
    TItem info;
    struct Nodo *next;
}TNodo;

typedef struct{
    TNodo *inicio, *fim;
    int tamanho;
}TLista;

typedef TLista *lista;

/*
Cria e retorna uma lista simplesmente encadeada.
    Utiliza aloca��o din�mica*/
lista criaLista();

/*
Finaliza a lista recebida por par�metro.
    Libera a mem�ria utilizada pela lista e por todos os seus nodos*/
void terminaLista(lista);

/*
Cria um nodo que recebe o elemento TItem e o liga � lista desejada.
    Par�metros: Lista e elemento(TItem).
    Retornos: 1 caso consiga alocar mem�ria, 0 caso n�o consiga.*/
int insereFinal(lista, TItem);

/*
Remove um nodo, que cont�m um elemento com id espec�fico, da lista e libera a mem�ria alocada.
    Par�metros: Lista e id do Produto.
    Retornos: 1 caso consiga remover, 0 caso n�o consiga.*/
int removeElemento(lista, unsigned long);

/*
Verifica se existe um nodoque cont�m um elemento com id espec�fico.
    Par�metros: Lista e id do Produto.
    Retornos: 1 caso exista, 0 caso n�o exista.*/
int verificaLista(lista, unsigned long);

/*
Retorna o endere�o de um nodo, que cont�m um elemento com id espec�fico.
    Par�metros: Lista e id do Produto.
    Retornos: endere�o caso exista, NULL caso n�o exista.*/
TNodo* getItem(lista, unsigned long);

#endif /*CARRINHO_TAD_H_INCLUDED*/
