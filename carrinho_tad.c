#include "carrinho_tad.h"
#include <stdlib.h>

lista criaLista(){
    lista l;

    l = (lista) malloc(sizeof(TLista));
    if(l!=NULL){
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
    }

    return l;
}

void terminaLista(lista l){
    TNodo *n;

    while(l->inicio!=NULL){
        n = l->inicio;
        l->inicio = l->inicio->next;
        free(n);
    }
    free(l);
}

int insereFinal(lista l, TItem i){
    TNodo *n;
    n=(TNodo*)malloc(sizeof(TNodo));
    if(n!=NULL){/*verificando se conseguiu alocar espaço de memória*/
        n->next = NULL;
        n->info = i;
        if(l->inicio==NULL)/*verificando se a lista está vazia*/
            l->inicio = n;
        else
            l->fim->next = n;

        l->fim = n;
        l->tamanho++;

        return 1;
    }else
        return 0;
}

int removeElemento(lista l, unsigned long id){
    TNodo *n, *ant;
    n = l->inicio;

    while(n!=NULL){
        if(n->info.idProduto == id){
            if(n==l->inicio){
                l->inicio = l->inicio->next;
            }else if(n==l->fim){
                l->fim = ant;
                l->fim->next = NULL;
            }else{
                ant->next = n->next;
            }
            free(n);
            l->tamanho--;

            return 1;
        }else{
            ant=n;
            n = n->next;
        }
    }
    return 0;
}

int verificaLista(lista l, unsigned long id){
/*Retorna 1 caso o item já esteja no carrinho ou 0 caso o item não esteja*/
    TNodo *n;

    n = l->inicio;
    while(n!=NULL)
        if(n->info.idProduto==id)
            return 1;
        else
            n = n->next;

    return 0;
}

TNodo* getItem(lista l, unsigned long id){
    TNodo *n;
    n = l->inicio;
    while(n!=NULL){
        if(n->info.idProduto == id)
            return n;
        n = n->next;
    }

    return n;
}


