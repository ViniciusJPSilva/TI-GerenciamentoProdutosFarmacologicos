#include <stdio.h>
#include <string.h>
#include "produto.h"
#include "funcGerais.h"
#include "entradaSaida.h"

/*=======================CADASTRO=======================*/
void cadastroProduto(){
    int sair;
    TProduto produto;
    FILE *arq;

    abrirArquivo(&arq, "produto.dat");

    if(arq!=NULL){
        do{
            printf("\n--------------------------------------------------\n");
            printf("---------------- Cadastro Produto ----------------");
            printf("\n--------------------------------------------------\n");

            printf("\n\t---Forne�a os dados do novo produto---");
            produto.id = novoIdProduto(arq);
            printf("\n\tID = %lu", produto.id);

            entradaNome(produto.nome);
            produto.quantidadeEstoque = 0;
            entradaPrecoUnit(&produto.precoUnitario);

            /*Gravando os dados no arquivo 'produto.dat'*/
            fseek(arq, 0, SEEK_END);
            fwrite(&produto, sizeof(TProduto), 1, arq);

            printf("\n--------- Produto Cadastrado com Sucesso ---------\n");
            printf("\n\tDeseja abandonar o cadastro?");
            escolhaSimNao(&sair);

        }while(sair!=1);
        fclose(arq);
    }else
        printf("\n\tN�o foi poss�vel abrir o arquivo!!\n");
}

unsigned long novoIdProduto(FILE *arq){
    unsigned long quantidade = 0;
    TProduto p;

    fseek(arq, 0, SEEK_SET);

    while(fread(&p, sizeof(TProduto), 1, arq)==1)
        if(p.id != 0)
            quantidade++;
        else
            return quantidade+1;

    return quantidade+1;
}


/*====================ATUALIZAR PRE�O====================*/
void attPrecoProduto(){
    int op, inv;
    FILE *arqProd, *arqHist;

    abrirArquivo(&arqProd, "produto.dat");
    abrirArquivo(&arqHist,"historicoPreco.dat");

    if(arqProd!=NULL && arqHist!=NULL){
        fseek(arqProd, 0, SEEK_END);
        if(ftell(arqProd)>0){
            do{
                printf("\n---------------------------------------------------\n");
                printf("------------ Atualizar Pre�o - Produto ------------");
                printf("\n---------------------------------------------------\n");

                printf("\n\t1 - Todos os Produtos");
                printf("\n\t2 - Um �nico Produto");
                printf("\n\t3 - Voltar ao Menu Principal");

                do{
                    printf("\n\tEscolha uma op��o: ");
                    scanf("%d", &op);

                    inv = 0;
                    switch(op){
                    case 1:
                        attPrecoTodos(arqProd, arqHist);
                        break;
                    case 2:
                        attPrecoUnico(arqProd, arqHist);
                        break;
                    case 3:
                        break;
                    default:
                        inv = 1;
                    }

                    if(inv)
                        printInvOption("Op��o");

                }while(inv);

            }while(op!=3);
        }else
            printf("\n\tN�o h� produtos cadastrados!!\n");

        fclose(arqProd);
        fclose(arqHist);
    }else
        printf("\n\tN�o foi possv�vel abrir os arquivos!!\n");
}

void attPrecoTodos(FILE *arqProd, FILE *arqHist){
    float porcentagem;
    int op, qtde=0;
    TProduto produto;

    printf("\n---------------------------------------------------\n");
    printf("------- Atualizar Pre�o - Todos os Produtos -------");
    printf("\n---------------------------------------------------\n");

    printf("\n-------------------- ATEN��O --------------------\n");
    printf("\n\tA atualiza��o ir� alterar os pre�os de TODOS os produtos!\n\tDeseja prosseguir com a atualiza��o?");
    escolhaSimNao(&op);
    if(op==1){
        op = tipoAttPreco();
        porcentagem = entradaPorcentagem();

        /*Loop que atualiza os pre�os unit�rios de todos os produtos*/
        fseek(arqProd, 0, SEEK_SET);
        while(fread(&produto, sizeof(TProduto), 1, arqProd)==1){
            if(op==1)
                produto.precoUnitario += produto.precoUnitario*(porcentagem/100);
            else
                produto.precoUnitario -= produto.precoUnitario*(porcentagem/100);

            /*Atualizando o arquivo 'produto.dat'*/
            fseek(arqProd, sizeof(TProduto)*qtde, SEEK_SET);
            fwrite(&produto, sizeof(TProduto), 1, arqProd);
            qtde++;
            fseek(arqProd, sizeof(TProduto)*qtde, SEEK_SET);

            atualizaHistorico(arqHist, produto);
        }

        printf("\n--------- Pre�os Atualizados com Sucesso ---------\n");

        printf("\n\tDeseja conferir as atualiza��es?");
        escolhaSimNao(&op);

        if(op==1)
            listagemProdutos(arqProd);
    }else
        printf("\n------------- Atualiza��o Cancelada -------------\n");
}

void attPrecoUnico(FILE *arqProd, FILE *arqHist){
    float porcentagem;
    int op, posicao;
    char data[11];
    TProduto produto;

    geraData(data);

    printf("\n----------------------------------------------------\n");
    printf("-------- Atualizar Pre�o - Um �nico Produto --------");
    printf("\n----------------------------------------------------\n");

    /*Permitindo uma listagem pr�via de todos os produtos, caso o usu�rio tenha se esquecido do ID*/
    printf("\n-------------------- ATEN��O --------------------\n");
    printf("\n\tA atualiza��o � realizada utilizando o ID!\n\tDeseja realizar uma listagem dos produtos?");
    escolhaSimNao(&op);
    if(op==1)
        listagemProdutos(arqProd);

    printf("\n");
    posicao = consultaProdutoID(arqProd);
    if(posicao!=-1){
        printf("\t-----------------------------------------");
        printf("\n\n\tDeseja prosseguir com a atualiza��o?"); /*Confirmando a atualiza��o*/
        escolhaSimNao(&op);

        if(op==1){
            op = tipoAttPreco();
            porcentagem = entradaPorcentagem();

            /*Atualizando o pre�o do produto*/
            fseek(arqProd, sizeof(TProduto)*posicao, SEEK_SET);
            fread(&produto, sizeof(TProduto), 1, arqProd);

            if(op==1)
                produto.precoUnitario += produto.precoUnitario*(porcentagem/100);
            else
                produto.precoUnitario -= produto.precoUnitario*(porcentagem/100);

            fseek(arqProd, sizeof(TProduto)*posicao, SEEK_SET);
            fwrite(&produto, sizeof(TProduto), 1, arqProd);

            atualizaHistorico(arqHist, produto);

            printf("\n\tNovo Pre�o Unit�rio = R$%.2f\n", produto.precoUnitario);
            printf("\n---------- Pre�o Atualizado com Sucesso ----------\n");
        }else
            printf("\n------------- Atualiza��o Cancelada -------------\n");
    }
}

int tipoAttPreco(){
    int op;
    do{
        printf("\n\tQual tipo de atualiza��o deseja realizar?\n\t1 - Aumentar Pre�o\n\t2 - Diminuir Pre�o");
        printf("\n\tEscolha uma op��o: ");
        scanf("%d", &op);

        if(op!=1 && op!=2)
            printInvOption("Op��o");
    }while(op!=1 && op!=2);
    return op;
}

float entradaPorcentagem(){
    float porcentagem;
    do{
        printf("\n\tForne�a a Porcentagem de altera��o: ");
        scanf("%f", &porcentagem);

        if(porcentagem<=0)
            printInvOption("Porcentagem");

    }while(porcentagem<=0);
    return porcentagem;
}


/*==================CONSULTA E LISTAGEM==================*/
int consultaProdutoID(FILE *arq){
    unsigned long id;
    int posicao;
    TProduto produto;

    printf("\n\tForne�a o id: ");
    scanf("%lu", &id);

    posicao = pesquisaProdutoID(arq, id);
    if(posicao!=-1){
        fseek(arq, posicao*sizeof(TProduto), SEEK_SET);
        fread(&produto, sizeof(TProduto), 1, arq);

        printf("\n\t-- Dados do Produto --\n");
        printTProduto(produto);
    }else
        printf("\n\tProduto inexistente!!!\n");

    return posicao;
}

int pesquisaProdutoID(FILE *arq, unsigned long id){
    int posicao = 0;
    TProduto produto;

    fseek(arq, 0, SEEK_SET);
    while(fread(&produto, sizeof(TProduto), 1, arq)==1){
        if(produto.id==id)
            return posicao;
        else
            posicao++;
    }

    return -1;
}

void listagemProdutos(FILE *arq){
    TProduto produto;

    printf("\n---------------------------------------------------\n");
    printf("---------------- Listagem Produtos ----------------");
    printf("\n---------------------------------------------------\n");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq) > 0){
        fseek(arq, 0, SEEK_SET);
        while(fread(&produto, sizeof(TProduto), 1, arq)==1){
            printTProduto(produto);
            printf("\t-----------------------------------------");
        }
    }else
        printf("\n\tNenhum produto cadastrado!!\n");
}

void printTProduto(TProduto produto){
    printf("\n\tID    = %lu", produto.id);
    printf("\n\tNome  = %s", produto.nome);
    printf("\n\tPre�o = R$%.2f", produto.precoUnitario);
    printf("\n\tQuantidade em estoque  = %u\n", produto.quantidadeEstoque);
}


/*======================FUN��ES GET======================*/
unsigned long getIDProduto(FILE *arq, int posicao){
    TProduto produto;

    fseek(arq, posicao*sizeof(TProduto), SEEK_SET);
    fread(&produto, sizeof(TProduto), 1, arq);

    return produto.id;
}

unsigned int getEstoqueProduto(FILE *arq, unsigned long id){
    int posicao;
    TProduto produto;

    posicao = pesquisaProdutoID(arq, id);
    if(posicao!=-1){
        fseek(arq, sizeof(TProduto)*posicao, SEEK_SET);
        fread(&produto, sizeof(TProduto), 1, arq);

        return produto.quantidadeEstoque;
    }

    return 0;
}

float getValorProduto(FILE *arq, unsigned long id){
    int posicao;
    TProduto produto;

    posicao = pesquisaProdutoID(arq, id);
    if(posicao!=-1){
        fseek(arq, sizeof(TProduto)*posicao, SEEK_SET);
        fread(&produto, sizeof(TProduto), 1, arq);

        return produto.precoUnitario;
    }

    return 0;
}

void getNomeProduto(unsigned long id, char *nome){
    int posicao;
    TProduto produto;

    FILE *arq;
    abrirArquivo(&arq, "produto.dat");

    posicao = pesquisaProdutoID(arq, id);
    if(posicao!=-1){
        fseek(arq, sizeof(TProduto)*posicao, SEEK_SET);
        fread(&produto, sizeof(TProduto), 1, arq);

        strcpy(nome, produto.nome);
    }
    fclose(arq);
}


/*===================ESTOQUE E HIST�RICO===================*/
void atualizaEstoque(FILE * arq, unsigned long id, int qtde){
    unsigned int posicao;
    TProduto produto;

    posicao = pesquisaProdutoID(arq, id); /*Recebe a posi��o*/
    fseek(arq, sizeof(TProduto)*posicao, SEEK_SET); /*Posiciona o 'cursor'*/
    fread(&produto, sizeof(TProduto), 1, arq); /*Recebe os dados*/
    produto.quantidadeEstoque += qtde; /*altera a quantidade*/
    fseek(arq, sizeof(TProduto)*posicao, SEEK_SET); /*Reposiciona o 'cursor'*/
    fwrite(&produto, sizeof(TProduto), 1, arq); /*Grava os dados*/
}

void atualizaHistorico(FILE *arqHist, TProduto produto){
    THistorico novoHist;
    char data[11];

    geraData(data);

    /*Atualizando o arquivo 'historicoPreco.dat'*/
    novoHist.idProduto = produto.id; /*ID*/
    strcpy(novoHist.dataAlteracao, data); /*Data da altera��o*/
    novoHist.valor = produto.precoUnitario; /*Novo valor*/
    fseek(arqHist, 0, SEEK_END);
    fwrite(&novoHist, sizeof(THistorico), 1, arqHist); /*Armazena os novos dados*/
}

int printaHistorico(FILE *arqUser,unsigned long id, int printa){
    int achou=0;
    THistorico item;

    FILE *arq;
    abrirArquivo(&arq,"historicoPreco.dat");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq) > 0){
        fseek(arq, 0, SEEK_SET);
        while(fread(&item, sizeof(THistorico), 1, arq)==1){
            if(id==item.idProduto){ /*Compara o id recebido com o id do item do hist�rico*/
                if(printa==0){
                    achou = 1;
                    break;
                }else{
                    if(arqUser==NULL){ /*Verifica onde deve ser feita a impress�o*/
                        printf("\n\tData Altera��o = %s", item.dataAlteracao);
                        printf("\n\tValor Alterado = R$%.2f\n", item.valor);
                        printf("\t----------------------------------------");
                    }else{
                        fprintf(arqUser, "\n\tData Altera��o = %s", item.dataAlteracao);
                        fprintf(arqUser, "\n\tValor Alterado = R$%.2f\n", item.valor);
                        fprintf(arqUser, "\t----------------------------------------");
                    }
                }
            }
        }
    }
    fclose(arq);
    return achou;
}



