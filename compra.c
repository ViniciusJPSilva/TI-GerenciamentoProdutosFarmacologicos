#include <stdio.h>
#include <string.h>
#include "compra.h"
#include "carrinho_tad.h"
#include "funcGerais.h"
#include "entradaSaida.h"
#include "fornecedor.h"
#include "vendedor.h"
#include "cliente.h"
#include "produto.h"
#include "notas.h"

/*=======================MENU=======================*/

void compraEvenda(int tipo){
    FILE *arqProd;
    abrirArquivo(&arqProd, "produto.dat");

    if(arqProd!=NULL){
        fseek(arqProd, 0, SEEK_END);
        if(ftell(arqProd) > 0){
            if(tipo==1)
                areaVenda(arqProd);
            else
                areaCompra(arqProd);
        }else
            printf("\n\tN�o h� produtos cadastrados!!\n");

        fclose(arqProd);
    }else
        printf("\n\tN�o foi poss�vel abrir o arquivo!!\n");
}

void areaVenda(FILE *arqProd){
    int op, inv;
    unsigned long idVendedor, idCliente;
    FILE *arq;

    abrirArquivo(&arq, "vendedor.dat");
    inv = selecionaVendedor(arq, &idVendedor); /*Autentica��o do Vendedor*/
    fclose(arq);

    if(!inv){
        do{
            /*Inicializando a lista de compras*/
            lista carrinho;
            carrinho = criaLista();

            abrirArquivo(&arq, "cliente.dat"); /*Valida��o do Cliente*/
            inv = selecionaCliente(arq, &idCliente);
            fclose(arq);

            if(!inv){
                do{
                    printf("\n-------------------------------------------------\n");
                    printf("--------------- Efetuar uma Venda ---------------");
                    printf("\n-------------------------------------------------\n");
                    printf("\n\t1 - Adicionar ou Alterar Item");
                    printf("\n\t2 - Remover Item");
                    printf("\n\t3 - Listagem dos Itens do Carrinho");
                    printf("\n\t4 - Finalizar Venda");
                    printf("\n\t5 - Abandonar Venda\n");

                    do{
                        printf("\n\tEscolha uma op��o: ");
                        scanf("%d", &op);

                        inv = 0;
                        switch(op){
                        case 1:
                            adicionarItem(arqProd, carrinho, 1);
                            break;
                        case 2:
                            removerItem(arqProd, carrinho);
                            break;
                        case 3:
                            listarCarrinho(arqProd, carrinho);
                            break;
                        case 4:
                            op = finalizarCarrinhoVenda(arqProd, carrinho, idVendedor, idCliente);
                            if(op==0)
                                op=5;
                            break;
                        case 5:
                            printf("\n\tDeseja abandonar a venda?");
                            escolhaSimNao(&op);
                            if(op==1)
                                op=5;
                            break;
                        default:
                            inv = 1;
                        }
                        if(inv)
                            printInvOption("Op��o");

                    }while(inv);
                }while (op != 5);
            }
            terminaLista(carrinho);

            printf("\n\tDeseja efetuar outra venda com o mesmo vendedor?");
            escolhaSimNao(&op);

        }while(op==1);
    }
}

void areaCompra(FILE *arqProd){
    int op, inv;
    unsigned long idFornc;
    FILE *arqFornc;

    lista carrinho; /*Inicializando a lista de compras*/
    carrinho = criaLista();

    abrirArquivo(&arqFornc, "fornecedor.dat");
    inv = selecionaFornecedor(arqFornc,&idFornc);
    fclose(arqFornc);

    if(!inv){
        do{
            printf("\n--------------------------------------------------\n");
            printf("--------------- Efetuar uma Compra ---------------");
            printf("\n--------------------------------------------------\n");
            printf("\n\t1 - Adicionar ou Alterar Item");
            printf("\n\t2 - Remover Item");
            printf("\n\t3 - Listagem dos Itens do Carrinho");
            printf("\n\t4 - Finalizar Compra");
            printf("\n\t5 - Abandonar Compra\n");

            do{
                printf("\n\tEscolha uma op��o: ");
                scanf("%d", &op);

                inv = 0;
                switch(op){
                case 1:
                    adicionarItem(arqProd, carrinho, 2);
                    break;
                case 2:
                    removerItem(arqProd, carrinho);
                    break;
                case 3:
                    listarCarrinho(arqProd, carrinho);
                    break;
                case 4:
                    op = finalizarCarrinhoCompra(arqProd, carrinho, idFornc);
                    if(op==0)
                        op=5;
                    break;
                case 5:
                    printf("\n\tDeseja abandonar as compras e voltar ao Menu Principal?");
                    escolhaSimNao(&op);
                    if(op==1)
                        op=5;
                    break;
                default:
                    inv = 1;
                }
                if(inv)
                    printInvOption("Op��o");

            }while(inv);
        }while (op != 5);
    }
    terminaLista(carrinho);
}


int selecionaFornecedor(FILE *arq, unsigned long *f){
    int op, posicao;

    printf("\n-------------------------------------------------\n");
    printf("------------ Selecionar o Fornecedor ------------");
    printf("\n-------------------------------------------------\n");

    fseek(arq, 0, SEEK_END); /*Verifica se h� vendedores cadastrados*/
    if(ftell(arq)>0){
        do{
            posicao = consultaForncID(arq);
            op=0;
            if(posicao==-1){
                printf("\tDeseja voltar ao menu principal?\n");
                escolhaSimNao(&op);
                if(op==1)
                    return 1;
            }
        }while(op==2);

        *f = getIDFornecedor(arq, posicao);
        return 0;
    }else
        printf("\n\tNenhum fornecedor cadastrado!!\n");

    return 1;
}

int selecionaVendedor(FILE *arq, unsigned long *v){
    int op;
    char senhaIn[20], passwd[20];

    printf("\n--------------------------------------------------\n");
    printf("------------ Autentica��o do Vendedor ------------");
    printf("\n--------------------------------------------------\n");

    fseek(arq, 0, SEEK_END); /*Verifica se h� vendedores cadastrados*/
    if(ftell(arq)>0){
        /*Entrada e valida��o do CPF*/
        do{
            *v = consultaVendCPF(arq); /*Retorna o id do vendedor*/
            if(*v==0){
                printf("\tDeseja voltar ao menu principal?\n");
                escolhaSimNao(&op);
                if(op==1)
                    return 1;
            }
        }while(*v==0);
        getSenhaVendedor(arq, *v, passwd); /*Recebendo a senha do vendedor*/

        op=3;
        do{
            printf("\n\t--Realize o login--\n");
            entradaSenha(senhaIn);                          /*Recebendo a senha do login*/
            if(strncmp(passwd,senhaIn,strlen(passwd))==0)   /*Autentica��o*/
                return 0;
            else{
                printf("\n\tSenha Incorreta! Tentativas Restantes: %d", op);
                op--;
            }
        }while(op>=0);

    }else
        printf("\n\tNenhum vendedor cadastrado!!\n");

    return 1;
}

int selecionaCliente(FILE *arq, unsigned long *c){
    int op, posicao;

    printf("\n------------------------------------------------\n");
    printf("------------- Selecionar o Cliente -------------");
    printf("\n------------------------------------------------\n");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq)>0){
        do{
            posicao = consultaClienteID(arq);
            op=0;
            if(posicao==-1){
                printf("\tDeseja cancelar a opera��o?\n");
                escolhaSimNao(&op);
                if(op==1)
                    return 1;
            }
        }while(op==2);

        *c = getIDCliente(arq, posicao);
        return 0;
    }else
        printf("\n\tNenhum cliente cadastrado!!\n");

    return 1;
}


/*=================ADICIONAR/ALTERAR=================*/
void adicionarItem(FILE *arqProd, lista carrinho, int operacao){
    int qtde, posicao, op;
    unsigned long idProd;

    printf("\n-------------------------------------------------\n");
    printf("----------- Adicionar ou Alterar Item -----------");
    printf("\n-------------------------------------------------\n");

    posicao = consultaProdutoID(arqProd); /*Entrada do ID, retorna a posi��o*/
    if(posicao!=-1){
        idProd = getIDProduto(arqProd, posicao); /*Pega o ID*/
        op = verificaLista(carrinho,idProd); /*Verifica se o item j� est� no carrinho*/

        if(op==0){
            entradaQuantidade(&qtde);

            if(operacao==1) /*Verifica se a opera��o � uma Venda*/
                if(getEstoqueProduto(arqProd,idProd)<qtde){ /*Verifica se a quantidade em estoque � suficiente*/
                    printf("\n\tN�o h� produtos suficientes em estoque!! Opera��o cancelada!\n");
                    return ;
                }

            adicionarAoCarrinho(arqProd, carrinho, idProd, qtde); /*Adiciona ao carrinho*/
            printf("\n----------- Item Adicionado com Sucesso -----------\n");

        }else{
            printf("\n\tO produto j� est� no carrinho! Deseja alterar a quantidade?");
            escolhaSimNao(&op);

            if(op==1){
                removeElemento(carrinho, idProd); /*Remove o item do carrinho e o adiciona novamente com a nova quantidade*/
                entradaQuantidade(&qtde);

                if(operacao==1)
                    if(getEstoqueProduto(arqProd,idProd)<qtde){ /*Verifica se a quantidade em estoque � suficiente*/
                        printf("\n\tN�o h� produtos suficientes em estoque!! Opera��o cancelada!\n");
                        return ;
                    }

                adicionarAoCarrinho(arqProd, carrinho, idProd, qtde); /*Adiciona ao carrinho*/
                printf("\n------------ Item Alterado com Sucesso ------------\n");
            }else
                printf("\n\tOpera��o Cancelada!!\n");
        }
    }

}

void entradaQuantidade(int *qtde){
    do{
        printf("\n\tForne�a a quantidade: ");
        scanf("%d", qtde);

        if(*qtde<=0)
            printf("\n\tQuantidade inv�lida!! Tente novamente.\n");
    }while(*qtde<=0);
}

void adicionarAoCarrinho(FILE *arqProd, lista carrinho, unsigned long idProduto, int quantidade){
    TItem item;

    item.idProduto = idProduto;
    item.quantidade = quantidade;
    item.valorUnitario = getValorProduto(arqProd, idProduto);

    insereFinal(carrinho, item);
}


/*======================REMOVER======================*/
void removerItem(FILE *arqProd, lista carrinho){
    int op;
    unsigned long idItem;
    TNodo *item;

    printf("\n------------------------------------------------\n");
    printf("----------------- Remover Item -----------------");
    printf("\n------------------------------------------------\n");

    if(carrinho->tamanho>0){ /*Verifica se o carrinho est� vazio*/
        printf("\n\tForne�a o ID do Produto que deseja excluir: ");
        scanf("%lu", &idItem);

        item = getItem(carrinho, idItem); /*Verifica se o carrinho possui o produto*/
        if(item!=NULL){
            printf("\n\t-- Dados do Item --\n");
            printaItem(arqProd, item);

            printf("\n\tDeseja prosseguir com a remo��o?"); /*Confrima��o*/
            escolhaSimNao(&op);

            if(op==1){
                if(removeElemento(carrinho, idItem)==1) /*Remove o produto*/
                    printf("\n------------ Item Removido com Sucesso ------------\n");
                else
                    printf("\n\tOcorreu um erro!! Remo��o cancelada!!\n");
            }else
                printf("\n\tRemo��o cancelada!!\n");
        }else
            printf("\n\tItem n�o encontrado!!\n");
    }else
        printf("\n\tO carrinho est� vazio!!\n");
}


/*=====================LISTAGEM=====================*/
void listarCarrinho(FILE *arqProd,lista carrinho){
    TNodo *n;
    n = carrinho->inicio;

    printf("\n------------------------------------------------\n");
    printf("-------- Listagem dos Itens do Carrinho --------");
    printf("\n------------------------------------------------\n");

    if(carrinho->tamanho > 0) /*Verifica se o carrinho est� vazio*/
        while(n!=NULL){
            printaItem(arqProd, n);
            printf("\t-----------------------------------------");
            n = n->next;
        }
    else
        printf("\n\tO carrinho est� vazio!!\n");
}

void printaItem(FILE *arqProd, TNodo *n){
    char nome[100];
    getNomeProduto(n->info.idProduto,nome);

    printf("\n\tID             : %lu", n->info.idProduto);
    printf("\n\tNome           : %s", nome);
    printf("\n\tQuantidade     : %u", n->info.quantidade);
    printf("\n\tValor unit�rio : R$%.2f\n", n->info.valorUnitario);
}


/*=====================FINALIZAR=====================*/
int finalizarCarrinhoVenda(FILE *arqProd, lista carrinho, unsigned long idVendedor, unsigned long idCliente){
    int op;
    unsigned long IdNotaFiscal;
    char dataCompra[11];
    float valorTotal = 0;

    TNodo *n;

    geraData(dataCompra);

    printf("\n------------------------------------------------\n");
    printf("------------- Finaliza��o da Venda -------------");
    printf("\n------------------------------------------------\n");

    if(carrinho->tamanho>0){
        printf("\n\tDeseja finalizar e confirmar a venda?"); /*Confirma��o*/
        escolhaSimNao(&op);

        if(op==1){
            /*Confirma��o/Altera��o da data da Venda*/
            printf("\n\tData Atual: %s\n\tDeseja alterar a data da venda?", dataCompra);
            setbuf(stdin, NULL);
            escolhaSimNao(&op);
            if(op==1)
                entradaData(dataCompra);

            /*Atualizando o estoque dos produtos*/
            n = carrinho->inicio;
            while(n!=NULL){
                atualizaEstoque(arqProd, n->info.idProduto, n->info.quantidade*(-1));
                valorTotal += n->info.valorUnitario * n->info.quantidade;
                n = n->next;
            }

            /*Criando uma nova nota Fiscal*/
            IdNotaFiscal = novaNotaFiscal(idVendedor,idCliente,dataCompra,valorTotal);

            /*Criando as notas de Item*/
            n = carrinho->inicio;
            while(n!=NULL){
                novoItemNotaFiscal(n->info.idProduto, IdNotaFiscal, n->info.quantidade, n->info.valorUnitario);
                n = n->next;
            }

            printf("\n---------- Venda Finalizada com Sucesso ----------\n");
        }else{
            printf("\n\tFinaliza��o cancelada!!\n");
            return 1;
        }
    }else{
        printf("\n\tO carrinho est� vazio!!\n");
        return 1;
    }

    return 0;
}

int finalizarCarrinhoCompra(FILE *arqProd, lista carrinho, unsigned long idFornecedor){
    int op;
    unsigned long IdNotaCompra;
    char dataCompra[11];
    float valorTotal = 0;

    TNodo *n;

    geraData(dataCompra);

    printf("\n-------------------------------------------------\n");
    printf("------------- Finaliza��o da Compra -------------");
    printf("\n-------------------------------------------------\n");

    if(carrinho->tamanho>0){
        printf("\n\tDeseja finalizar e confirmar a compra?");
        escolhaSimNao(&op);

        if(op==1){
            /*Confirma��o/Altera��o da data da Compra*/
            printf("\n\tData Atual: %s\n\tDeseja alterar a data da compra?", dataCompra);
            setbuf(stdin, NULL);
            escolhaSimNao(&op);
            if(op==1)
                entradaData(dataCompra);

            /*Atualizando o estoque dos produtos*/
            n = carrinho->inicio;
            while(n!=NULL){
                atualizaEstoque(arqProd, n->info.idProduto, n->info.quantidade);
                valorTotal += n->info.valorUnitario * n->info.quantidade;
                n = n->next;
            }

            /*Criando uma nova nota de compra*/
            IdNotaCompra = novaNotaCompra(idFornecedor, dataCompra, valorTotal);

            /*Criando as notas de Item*/
            n = carrinho->inicio;
            while(n!=NULL){
                novoItemNotaCompra(n->info.idProduto, IdNotaCompra, n->info.quantidade, n->info.valorUnitario);
                n = n->next;
            }

            printf("\n---------- Compra Finalizada com Sucesso ----------\n");
        }else{
            printf("\n\tFinaliza��o cancelada!!\n");
            return 1;
        }
    }else{
        printf("\n\tO carrinho est� vazio!!\n");
        return 1;
    }

    return 0;
}


