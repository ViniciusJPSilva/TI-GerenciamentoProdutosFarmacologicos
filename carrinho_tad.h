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
    Utiliza alocação dinâmica*/
lista criaLista();

/*
Finaliza a lista recebida por parâmetro.
    Libera a memória utilizada pela lista e por todos os seus nodos*/
void terminaLista(lista);

/*
Cria um nodo que recebe o elemento TItem e o liga à lista desejada.
    Parâmetros: Lista e elemento(TItem).
    Retornos: 1 caso consiga alocar memória, 0 caso não consiga.*/
int insereFinal(lista, TItem);

/*
Remove um nodo, que contém um elemento com id específico, da lista e libera a memória alocada.
    Parâmetros: Lista e id do Produto.
    Retornos: 1 caso consiga remover, 0 caso não consiga.*/
int removeElemento(lista, unsigned long);

/*
Verifica se existe um nodoque contém um elemento com id específico.
    Parâmetros: Lista e id do Produto.
    Retornos: 1 caso exista, 0 caso não exista.*/
int verificaLista(lista, unsigned long);

/*
Retorna o endereço de um nodo, que contém um elemento com id específico.
    Parâmetros: Lista e id do Produto.
    Retornos: endereço caso exista, NULL caso não exista.*/
TNodo* getItem(lista, unsigned long);

#endif /*CARRINHO_TAD_H_INCLUDED*/
