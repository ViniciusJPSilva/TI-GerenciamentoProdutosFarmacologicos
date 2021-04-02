#include <stdio.h>
#include <string.h>
#include "notas.h"
#include "funcGerais.h"
#include "produto.h"
#include "vendedor.h"
#include "cliente.h"

/*======================NOTA FISCAL======================*/
unsigned long novaNotaFiscal(unsigned long idVendedor, unsigned long idCliente, char *data, float valTotal){
    TNotaFiscal novaNota;

    FILE *arq;
    abrirArquivo(&arq, "notaFiscal.dat");

    if(arq!=NULL){
        novaNota.id = novoIdNotaCompra(arq); /*Gerando o ID*/
        novaNota.idVendedor = idVendedor;
        novaNota.idCliente = idCliente;
        strcpy(novaNota.dataCompra, data);
        novaNota.ValorTotal = valTotal;

        fseek(arq, 0, SEEK_END);
        fwrite(&novaNota, sizeof(TNotaFiscal), 1, arq); /*Armazenando os dados da nova nota*/

        fclose(arq);
        return novaNota.id;
    }else
        return 0;
}

unsigned long novoIdNotaFiscal(FILE *arq){
    unsigned long quantidade = 0;
    TNotaFiscal nf;

    fseek(arq, 0, SEEK_SET);
    while(fread(&nf, sizeof(TNotaFiscal), 1, arq)==1)
        if(nf.id != 0)
            quantidade++;
        else
            return quantidade+1;

    return quantidade+1;
}

void novoItemNotaFiscal(unsigned long idProduto, unsigned long idNotaFiscal, unsigned long quantidade, float valVenda){
    TItemNotaFiscal novoItem;

    FILE *arq;
    abrirArquivo(&arq, "itemNotaFiscal.dat");

    if(arq!=NULL){
        novoItem.id = novoIdItemNotaFiscal(arq); /*Gerando o ID*/
        novoItem.idProduto = idProduto;
        novoItem.idNotaFiscal = idNotaFiscal;
        novoItem.quantidade = quantidade;
        novoItem.valorVenda = valVenda;

        fseek(arq, 0, SEEK_END);
        fwrite(&novoItem, sizeof(TItemNotaFiscal), 1, arq); /*Armazenando os novos dados*/

        fclose(arq);
    }
}

unsigned long novoIdItemNotaFiscal(FILE *arq){
    unsigned long quantidade = 0;
    TItemNotaFiscal ni;

    fseek(arq, 0, SEEK_SET);
    while(fread(&ni, sizeof(TItemNotaFiscal), 1, arq)==1)
        if(ni.id != 0)
            quantidade++;
        else
            return quantidade+1;

    return quantidade+1;
}

int getNotaFiscal(unsigned long id, TNotaFiscal *nota){
    int achou=0;
    FILE *arq;
    abrirArquivo(&arq,"notaFiscal.dat");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq) > 0){
        fseek(arq, 0, SEEK_SET);
        while(fread(nota, sizeof(TNotaFiscal), 1, arq)==1){
            if(id==nota->id){
                achou=1;
                break;
            }
        }
    }
    fclose(arq);
    return achou;
}

void printaItemNotaFiscal(FILE *arqUser, unsigned long id){
    char nome[100];
    TItemNotaFiscal item;

    FILE *arq;
    abrirArquivo(&arq,"itemNotaFiscal.dat");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq) > 0){
        fseek(arq, 0, SEEK_SET);
        while(fread(&item, sizeof(TItemNotaFiscal), 1, arq)==1){
            if(id==item.idNotaFiscal){  /*Compara os ID's: Id do parâmetro (alguma nota Fiscal) e sua respectiva nota Fiscal*/
                if(arqUser==NULL){      /*Verifica se deve imprimir na tela ou em um arquivo*/
                    printf("\n\tID Produto     = %lu", item.idProduto);
                    getNomeProduto(item.idProduto, nome);
                    printf("\n\tNome           = %s", nome);
                    printf("\n\tQuantidade     = %u", item.quantidade);
                    printf("\n\tValor Unit.    = R$%.2f\n", item.valorVenda);
                    printf("\t----------------------------------------");
                }else{
                    fprintf(arqUser, "\n\tID Produto     = %lu", item.idProduto);
                    getNomeProduto(item.idProduto, nome);
                    fprintf(arqUser, "\n\tNome           = %s", nome);
                    fprintf(arqUser, "\n\tQuantidade     = %u", item.quantidade);
                    fprintf(arqUser, "\n\tValor Unit.    = R$%.2f\n", item.valorVenda);
                    fprintf(arqUser, "\t----------------------------------------");
                }
            }
        }
    }
    fclose(arq);
}


/*======================NOTA COMPRA======================*/
unsigned long novaNotaCompra(unsigned long idFornecedor, char *data, float valTotal){
    TNotaCompra novaNota;

    FILE *arq;
    abrirArquivo(&arq, "notaCompra.dat");

    if(arq!=NULL){
        novaNota.id = novoIdNotaCompra(arq); /*Gerando o ID*/
        novaNota.idFornecedor = idFornecedor;
        strcpy(novaNota.dataCompra, data);
        novaNota.valorTotal = valTotal;

        fseek(arq, 0, SEEK_END);
        fwrite(&novaNota, sizeof(TNotaCompra), 1, arq); /*Armazenando os dados da nova nota*/

        fclose(arq);
        return novaNota.id;
    }else
        return 0;
}

unsigned long novoIdNotaCompra(FILE *arq){
    unsigned long quantidade = 0;
    TNotaCompra nc;

    fseek(arq, 0, SEEK_SET);
    while(fread(&nc, sizeof(TNotaCompra), 1, arq)==1)
        if(nc.id != 0)
            quantidade++;
        else
            return quantidade+1;

    return quantidade+1;
}

void novoItemNotaCompra(unsigned long idProduto, unsigned long idNotaCompra, unsigned long quantidade, float valUnitario){
    TItemNotaCompra novoItem;

    FILE *arq;
    abrirArquivo(&arq, "itemNotaCompra.dat");

    if(arq!=NULL){
        novoItem.id = novoIdItemNotaCompra(arq); /*Gerando o novo ID*/
        novoItem.idProduto = idProduto;
        novoItem.idNotaCompra = idNotaCompra;
        novoItem.quantidade = quantidade;
        novoItem.valorUnitario = valUnitario;

        fseek(arq, 0, SEEK_END);
        fwrite(&novoItem, sizeof(TItemNotaCompra), 1, arq); /*Armazenando os novos dados*/

        fclose(arq);
    }
}

unsigned long novoIdItemNotaCompra(FILE *arq){
    unsigned long quantidade = 0;
    TItemNotaCompra ni;

    fseek(arq, 0, SEEK_SET);
    while(fread(&ni, sizeof(TItemNotaCompra), 1, arq)==1)
        if(ni.id != 0)
            quantidade++;
        else
            return quantidade+1;

    return quantidade+1;
}

int getNotaCompra(unsigned long id, TNotaCompra *nota){
    int achou=0;
    FILE *arq;
    abrirArquivo(&arq,"notaCompra.dat");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq) > 0){
        fseek(arq, 0, SEEK_SET);
        while(fread(nota, sizeof(TNotaCompra), 1, arq)==1){
            if(id==nota->id){ /*Compara os IDs*/
                achou=1;
                break;
            }
        }
    }
    fclose(arq);
    return achou;
}

void printaItemNotaCompra(FILE *arqUser, unsigned long id){
    char nome[100];
    TItemNotaCompra item;

    FILE *arq;
    abrirArquivo(&arq,"itemNotaCompra.dat");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq) > 0){
        fseek(arq, 0, SEEK_SET);
        while(fread(&item, sizeof(TItemNotaCompra), 1, arq)==1){
            if(id==item.idNotaCompra){  /*Compara os ID's: Id do parâmetro (alguma nota Compra) e sua respectiva nota Compra*/
                if(arqUser==NULL){      /*Verifica se deve imprimir na tela ou em um arquivo*/
                    printf("\n\tID Produto     = %lu", item.idProduto);
                    getNomeProduto(item.idProduto, nome);
                    printf("\n\tNome           = %s", nome);
                    printf("\n\tQuantidade     = %u", item.quantidade);
                    printf("\n\tValor Unit.    = R$%.2f\n", item.valorUnitario);
                    printf("\t----------------------------------------");
                }else{
                    fprintf(arqUser, "\n\tID Produto     = %lu", item.idProduto);
                    getNomeProduto(item.idProduto, nome);
                    fprintf(arqUser, "\n\tNome           = %s", nome);
                    fprintf(arqUser, "\n\tQuantidade     = %u", item.quantidade);
                    fprintf(arqUser, "\n\tValor Unit.    = R$%.2f\n", item.valorUnitario);
                    fprintf(arqUser, "\t----------------------------------------");
                }
            }
        }
    }
    fclose(arq);
}


/*=====================VERIFICADORES=====================*/
int verificaVendDataNotaFiscal(unsigned int id, char *data, int printa, int mes, FILE *arqUser){
    int achou=0, mm;
    char nome[100];
    TNotaFiscal nota;

    FILE *arq;
    abrirArquivo(&arq,"notaFiscal.dat");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq) > 0){
        fseek(arq, 0, SEEK_SET);
        while(fread(&nota, sizeof(TNotaFiscal), 1, arq)==1){ /*Loop que passa por todas as notas Fiscais*/
            mm = (nota.dataCompra[3]-48)*10+(nota.dataCompra[4]-48); /*Transforma o mês char de nota.dataCompra para int*/
            /*Compara idVendedor com id (parâmetro), data inteira e o mês.
                Se data = "NULL", compara apenas o mês.
                Se mês = 0, compara apenas a data*/
            if(id==nota.idVendedor && (strcmp(data,nota.dataCompra)==0 || mes==mm)){
                if(printa==0){ /*Verifica se o usuário quer printar ou apenas saber se há Notas com idVendedor = id (parâmetro)*/
                    achou=1;
                    break;
                }else if(arqUser==NULL){ /*Caso queira printar, verifica se a impressão deve ser feita na tela (arqUser = NULL) ou em um arquivo*/
                    printf("\n\tID Nota Fiscal: %lu", nota.id);
                    getNomeCliente(nota.idCliente, nome);
                    printf("\n\n\tID Cliente : %lu\n\tNome: %s\n", nota.idCliente, nome);
                    if(mes==mm) /*Printa a data caso a verificação seja pelo mês*/
                        printf("\n\tData da Compra : %s", nota.dataCompra);
                    printf("\n\tValor Total : R$%.2f\n", nota.ValorTotal);
                    printf("\t----------------------------------------");
                    printaItemNotaFiscal(NULL, nota.id); /*Printa todos os itens nota Fiscal relacionados a nota Fiscal corrente*/
                    printf("\n\n--------------------------------------------------\n");

                }else{
                    fprintf(arqUser, "\n\tID Nota Fiscal: %lu", nota.id);
                    getNomeCliente(nota.idCliente, nome);
                    fprintf(arqUser, "\n\n\tID Cliente : %lu\n\tNome: %s\n", nota.idCliente, nome);
                    if(mes==mm) /*Printa a data caso a verificação seja pelo mês*/
                        fprintf(arqUser, "\n\tData da Compra : %s", nota.dataCompra);
                    fprintf(arqUser, "\n\n\tValor Total : R$%.2f\n", nota.ValorTotal);
                    fprintf(arqUser, "\t----------------------------------------");
                    printaItemNotaFiscal(arqUser, nota.id); /*Printa todos os itens nota Fiscal relacionados a nota Fiscal corrente*/
                    fprintf(arqUser, "\n\n--------------------------------------------------\n");
                }
            }
        }
    }
    fclose(arq);
    return achou;
}

int verificaClienteDataNotaFiscal(unsigned int id, char *data, int printa, FILE *arqUser){
    int achou=0;
    char nome[100];
    TNotaFiscal nota;

    FILE *arq;
    abrirArquivo(&arq,"notaFiscal.dat");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq) > 0){
        fseek(arq, 0, SEEK_SET);
        while(fread(&nota, sizeof(TNotaFiscal), 1, arq)==1){ /*Loop que passa por todas as notas Fiscais*/
            if(id==nota.idCliente && strcmp(data,nota.dataCompra)==0){ /*Verifica se idCliente = id (parâmetro) e se dataCompra = data (parâmetro)*/
                if(printa==0){ /*Verifica se o usuário quer printar ou apenas saber se há Notas com idCliente = id (parâmetro)*/
                    achou=1;
                    break;
                }else if(arqUser==NULL){ /*Caso queira printar, verifica se a impressão deve ser feita na tela (arqUser = NULL) ou em um arquivo*/
                    printf("\n\tID Nota Fiscal: %lu", nota.id);
                    getNomeVendedor(nota.idVendedor, nome);
                    printf("\n\n\tID Vendedor : %lu\n\tNome: %s\n", nota.idVendedor, nome);
                    printf("\n\tValor Total : R$%.2f\n", nota.ValorTotal);
                    printf("\t----------------------------------------");
                    printaItemNotaFiscal(NULL, nota.id); /*Printa todos os itens nota Fiscal relacionados a nota Fiscal corrente*/
                    printf("\n\n--------------------------------------------------\n");

                }else{
                    fprintf(arqUser, "\n\tID Nota Fiscal: %lu", nota.id);
                    getNomeVendedor(nota.idVendedor, nome);
                    fprintf(arqUser, "\n\n\tID Vendedor : %lu\n\tNome: %s\n", nota.idVendedor, nome);
                    fprintf(arqUser, "\n\n\tValor Total : R$%.2f\n", nota.ValorTotal);
                    fprintf(arqUser, "\t----------------------------------------");
                    printaItemNotaFiscal(arqUser, nota.id); /*Printa todos os itens nota Fiscal relacionados a nota Fiscal corrente*/
                    fprintf(arqUser, "\n\n--------------------------------------------------\n");
                }
            }
        }
    }
    fclose(arq);
    return achou;
}

int verificaClienteIntervaloNotaFiscal(unsigned int id, char *dataMenor, char *dataMaior, int printa, FILE *arqUser){
    int achou=0;
    char nome[100];
    TNotaFiscal nota;

    FILE *arq;
    abrirArquivo(&arq,"notaFiscal.dat");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq) > 0){
        fseek(arq, 0, SEEK_SET);
        while(fread(&nota, sizeof(TNotaFiscal), 1, arq)==1){ /*Loop que passa por todas as notas Fiscais*/
            /*Verifica se idCliente = id (parâmetro) e se dataCompra está entre dataMenor e dataMaior*/
            if(id==nota.idCliente && (verificaDataMenor(dataMenor,nota.dataCompra) && verificaDataMenor(nota.dataCompra,dataMaior))){
                if(printa==0){ /*Verifica se o usuário quer printar ou apenas saber se há Notas com idCliente = id (parâmetro)*/
                    achou=1;
                    break;
                }else if(arqUser==NULL){ /*Caso queira printar, verifica se a impressão deve ser feita na tela (arqUser = NULL) ou em um arquivo*/
                    printf("\n\tID Nota Fiscal: %lu", nota.id);
                    getNomeVendedor(nota.idVendedor, nome);
                    printf("\n\n\tID Vendedor : %lu\n\tNome: %s\n", nota.idVendedor, nome);

                    printf("\n\tData da Compra : %s", nota.dataCompra);
                    printf("\n\tValor Total : R$%.2f\n", nota.ValorTotal);
                    printf("\t----------------------------------------");
                    printaItemNotaFiscal(NULL, nota.id); /*Printa todos os itens nota Fiscal relacionados a nota Fiscal corrente*/
                    printf("\n\n--------------------------------------------------\n");

                }else{
                    fprintf(arqUser, "\n\tID Nota Fiscal: %lu", nota.id);
                    getNomeVendedor(nota.idVendedor, nome);
                    fprintf(arqUser, "\n\n\tID Vendedor : %lu\n\tNome: %s\n", nota.idVendedor, nome);

                    fprintf(arqUser,"\n\tData da Compra : %s", nota.dataCompra);
                    fprintf(arqUser, "\n\n\tValor Total : R$%.2f\n", nota.ValorTotal);
                    fprintf(arqUser, "\t----------------------------------------");
                    printaItemNotaFiscal(arqUser, nota.id); /*Printa todos os itens nota Fiscal relacionados a nota Fiscal corrente*/
                    fprintf(arqUser, "\n\n--------------------------------------------------\n");
                }
            }
        }
    }
    fclose(arq);
    return achou;
}

float verificaMaiorValorVendas(int mes, char *dataMenor, char *dataMaior){
    int mm;
    float maiorValor=0, valorVend;
    TNotaFiscal nota;
    TVendedor vend;

    FILE *arqNota;
    abrirArquivo(&arqNota,"notaFiscal.dat");
    FILE *arqVend;
    abrirArquivo(&arqVend,"vendedor.dat");

    fseek(arqNota, 0, SEEK_END);
    if(ftell(arqNota) > 0){

        fseek(arqVend,0,SEEK_SET);
        while(fread(&vend, sizeof(TVendedor), 1, arqVend)==1){ /*Loop dos Vendedores*/
            valorVend=0;

            fseek(arqNota, 0, SEEK_SET);
            while(fread(&nota, sizeof(TNotaFiscal), 1, arqNota)==1){ /*Loop das Notas Fiscais*/
                mm = (nota.dataCompra[3]-48)*10+(nota.dataCompra[4]-48);
                if(nota.idVendedor==vend.id && ((verificaDataMenor(dataMenor,nota.dataCompra) && verificaDataMenor(nota.dataCompra,dataMaior))  ||  mm==mes)){ /*Verificando id e mês*/
                    valorVend += nota.ValorTotal; /*Incrementando o valor total em vendas do vendedor*/
                }
            }
            if(valorVend > maiorValor) /*Verificando se o valor encontrado é maior*/
                maiorValor = valorVend;
        }
    }
    fclose(arqNota);
    fclose(arqVend);

    return maiorValor; /*Retornando o maior valor em vendas encontrado*/
}

void printaVendMaiorValorVendas(float maiorValor, int mes, char *dataMenor, char *dataMaior, FILE *arqUser){
    int mm;
    float valorVend;
    TNotaFiscal nota;
    TVendedor vend;

    FILE *arqNota;
    abrirArquivo(&arqNota,"notaFiscal.dat");
    FILE *arqVend;
    abrirArquivo(&arqVend,"vendedor.dat");

    fseek(arqNota, 0, SEEK_END);
    if(ftell(arqNota) > 0){

        fseek(arqVend,0,SEEK_SET);
        while(fread(&vend, sizeof(TVendedor), 1, arqVend)==1){ /*Loop dos Vendedores*/
            valorVend=0;

            fseek(arqNota, 0, SEEK_SET);
            while(fread(&nota, sizeof(TNotaFiscal), 1, arqNota)==1){ /*Loop das Notas Fiscais*/
                mm = (nota.dataCompra[3]-48)*10+(nota.dataCompra[4]-48);
                if(nota.idVendedor==vend.id && ((verificaDataMenor(dataMenor,nota.dataCompra) && verificaDataMenor(nota.dataCompra,dataMaior))  ||  mm==mes)){ /*Verificando id e mês*/
                    valorVend += nota.ValorTotal; /*Incrementando o valor total em vendas do vendedor*/
                }
            }

            if(valorVend == maiorValor){ /*Verificando se o valor encontrado é igual ao maior valor*/
                if(arqUser==NULL){
                    printf("\n\tID Vendedor : %lu\n\tNome: %s\n", vend.id, vend.nome);
                }else{
                    fprintf(arqUser,"\n\tID Vendedor : %lu\n\tNome: %s\n", vend.id, vend.nome);
                }
            }
        }
    }
    fclose(arqNota);
    fclose(arqVend);
}




