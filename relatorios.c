#include <stdio.h>
#include <string.h>
#include "relatorios.h"
#include "entradaSaida.h"
#include "funcGerais.h"
#include "notas.h"
#include "vendedor.h"
#include "fornecedor.h"
#include "cliente.h"
#include "produto.h"

void areaRelatorios(){
    int op, tipo, inv;
    do{
        printf("\n--------------------------------------------------\n");
        printf("------------------- Relatórios -------------------");
        printf("\n--------------------------------------------------\n");

        printf("\n\t1 - Nota Fiscal e Itens Associados");
        printf("\n\t2 - Compra e Itens Associados");
        printf("\n\t3 - Compras efetuadas por um Cliente - Data Específica");
        printf("\n\t4 - Compras efetuadas por um Cliente - Intervalo de Datas");
        printf("\n\t5 - Vendas efetuadas por um Vendedor - Dia Específico");
        printf("\n\t6 - Vendas efetuadas por um Vendedor - Mês");
        printf("\n\t7 - Vendedor(es) com maior valor em Vendas - Mês");
        printf("\n\t8 - Vendedor(es) com maior valor em Vendas - Intervalo de Datas");
        printf("\n\t9 - Histórico de valor de venda de um determinado produto");
        printf("\n\t10 - Voltar ao Menu Principal");

        do{
            printf("\n\tEscolha uma opção: ");
            scanf("%d", &op);

            if(op<1 || op>10)
                printInvOption("Opção");
        }while(op<1 || op>10);

        do{
            if(op!=10){ /*Entrada do tipo de impressão*/
                printf("\n\tComo quer o relatório?\n\t1 - Tela do Dispositivo\n\t2 - Arquivo");
                 do{
                    printf("\n\tEscolha uma opção: ");
                    scanf("%d", &tipo);

                    if(tipo<1 || tipo>2)
                        printInvOption("Opção");
                }while(tipo<1 || tipo>2);
            }

            inv = 0;
            switch(op){ /*Chamada das demais funções*/
            case 1:
                relatorioNotaFiscal(tipo);
                break;
            case 2:
                relatorioNotaCompra(tipo);
                break;
            case 3:
                relatorioComprasClienteData(tipo);
                break;
            case 4:
                relatorioComprasClienteIntervalo(tipo);
                break;
            case 5:
                relatorioVendasVendedorDia(tipo);
                break;
            case 6:
                relatorioVendasVendedorMes(tipo);
                break;
            case 7:
                relatorioMaiorValorVendedorMes(tipo);
                break;
            case 8:
                relatorioMaiorValorVendedorIntervalo(tipo);
                break;
            case 9:
                relatorioHistorico(tipo);
                break;
            case 10:
                break;
            default:
                inv = 1;
            }

            if(inv)
                printInvOption("Opção");

        }while(inv);

    }while (op != 10);

}


void relatorioNotaFiscal(int tipo){
    int valido;
    char nome[100];
    unsigned long id;
    TNotaFiscal nota;
    FILE *arq = NULL;

    printf("\n---------------------------------------------------\n");
    printf("------------- Relatório - Nota Fiscal -------------");
    printf("\n---------------------------------------------------\n");

    printf("\n\tForneça o ID da Nota Fiscal: ");
    scanf("%lu", &id);

    valido = getNotaFiscal(id, &nota); /*Verifica se a nota existe e recebe os dados da mesma pelo argumento 2*/

    if(valido){
        if(tipo==1){ /*Impressão em tela*/
            printLogo();

            printf("\n\tID Nota Fiscal: %lu", nota.id);

            getNomeVendedor(nota.idVendedor, nome); /*Pegando o nome do vendedor*/
            printf("\n\n\tID Vendedor: %lu\n\tNome: %s", nota.idVendedor, nome);

            getNomeCliente(nota.idCliente, nome); /*Pegando o nome do cliente*/
            printf("\n\n\tID Cliente : %lu\n\tNome: %s", nota.idCliente, nome);

            printf("\n\n\tData da Compra : %s", nota.dataCompra);
            printf("\n\tValor Total    : R$%.2f\n", nota.ValorTotal);

            printf("\t----------------------------------------");
            printf("\n\n\t------------------ITENS-----------------");
            printaItemNotaFiscal(NULL, nota.id); /*Printando os dados dos itens pertencentes a essa nota*/
        }else{ /*Impressão em arquivo*/
            criaTXT(&arq); /*Criando arquivo .txt*/

            if(arq!=NULL){
                fprintf(arq,"\n--------------------------------------------------\n");
                fprintf(arq,"--- LOUCO DAS PEDRAS - PRODUTOS FARMACOLÓGICOS ---");
                fprintf(arq,"\n--------------------------------------------------\n");

                fprintf(arq, "\n\tID Nota Fiscal: %lu", nota.id);

                getNomeVendedor(nota.idVendedor, nome); /*Pegando o nome do vendedor*/
                fprintf(arq, "\n\n\tID Vendedor: %lu\n\tNome: %s", nota.idVendedor, nome);

                getNomeCliente(nota.idCliente, nome); /*Pegando o nome do cliente*/
                fprintf(arq, "\n\n\tID Cliente : %lu\n\tNome: %s", nota.idCliente, nome);

                fprintf(arq, "\n\n\tData da Compra : %s", nota.dataCompra);
                fprintf(arq, "\n\tValor Total    : R$%.2f\n", nota.ValorTotal);

                fprintf(arq, "\t----------------------------------------");
                fprintf(arq, "\n\n\t------------------ITENS-----------------");
                printaItemNotaFiscal(arq, nota.id); /*Printando os dados dos itens pertencentes a essa nota*/

                fclose(arq);
                printf("\n\t--- Arquivo criado com sucesso!! ---");
            }else
                printf("\n\tNão foi possível criar o arquivo! Operação cancelada!\n");
        }
    }else
        printf("\n\t--- Nota Fiscal não encontrada ---");
}

void relatorioNotaCompra(int tipo){
    int valido;
    char nome[100];
    unsigned long id;
    TNotaCompra nota;
    FILE *arq = NULL;

    printf("\n---------------------------------------------------\n");
    printf("------------- Relatório - Nota Compra -------------");
    printf("\n---------------------------------------------------\n");

    printf("\n\tForneça o ID da Nota Compra: ");
    scanf("%lu", &id);

    valido = getNotaCompra(id, &nota); /*Verifica se a nota existe e recebe os dados da mesma pelo argumento 2*/

    if(valido){
        if(tipo==1){ /*Impressão em tela*/
            printLogo();

            printf("\n\tID Nota Compra: %lu", nota.id);

            getNomeFornecedor(nota.idFornecedor, nome); /*Pegando o nome do fornecedor*/
            printf("\n\n\tID Fornecedor: %lu\n\tNome: %s", nota.idFornecedor, nome);

            printf("\n\n\tData da Compra : %s", nota.dataCompra);
            printf("\n\tValor Total    : %.2f\n", nota.valorTotal);

            printf("\t----------------------------------------");
            printf("\n\n\t------------------ITENS-----------------");
            printaItemNotaCompra(NULL, nota.id); /*Printando os dados dos itens pertencentes a essa nota*/
        }else{ /*Impressão em arquivo*/
            criaTXT(&arq); /*Criando arquivo .txt*/

            if(arq!=NULL){
                fprintf(arq,"\n--------------------------------------------------\n");
                fprintf(arq,"--- LOUCO DAS PEDRAS - PRODUTOS FARMACOLÓGICOS ---");
                fprintf(arq,"\n--------------------------------------------------\n");

                fprintf(arq,"\n\tID Nota Compra: %lu", nota.id);

                getNomeFornecedor(nota.idFornecedor, nome); /*Pegando o nome do fornecedor*/
                fprintf(arq, "\n\n\tID Fornecedor: %lu\n\tNome: %s", nota.idFornecedor, nome);

                fprintf(arq, "\n\n\tData da Compra : %s", nota.dataCompra);
                fprintf(arq, "\n\tValor Total    : %.2f\n", nota.valorTotal);

                fprintf(arq, "\t----------------------------------------");
                fprintf(arq, "\n\n\t------------------ITENS-----------------");
                printaItemNotaCompra(arq, nota.id); /*Printando os dados dos itens pertencentes a essa nota*/

                fclose(arq);
                printf("\n\t--- Arquivo criado com sucesso!! ---");
            }else
                printf("\n\tNão foi possível criar o arquivo! Operação cancelada!\n");
        }
    }else
       printf("\n\t--- Nota Fiscal não encontrada ---");
}


void relatorioComprasClienteData(int tipo){
    int valido;
    char nome[100], data[11];
    unsigned long id;
    FILE *arq = NULL;

    printf("\n------------------------------------------------------\n");
    printf("- Compras efetuadas por um Cliente - Data Específica -");
    printf("\n------------------------------------------------------\n");

    printf("\n\tForneça o ID do Cliente: ");
    setbuf(stdin, NULL);
    scanf("%lu", &id);

    abrirArquivo(&arq, "cliente.dat");
    valido = pesquisaClienteID(arq, id); /*Verifica se o cliente existe*/
    fclose(arq);

    if(valido!=-1){
        entradaData(data); /*Entrada da data específica*/
        valido = verificaClienteDataNotaFiscal(id, data, 0, NULL); /*Verifica se existem notas que correspondem às duas condições do relatório: id do cliente e data*/

        if(valido){
            if(tipo==1){ /*Tipo de impressão*/
                printLogo();
                printf("\n-------- Compras efetuadas por um Cliente --------\n");

                printf("\n\tData Específica: %s", data);

                getNomeCliente(id, nome); /*Pegando o nome do cliente*/
                printf("\n\n\tID Cliente: %lu\n\tNome: %s", id, nome);

                printf("\n\n--------------------------------------------------\n");
                printf("--------------- Notas e seus Itens ---------------\n");
                verificaClienteDataNotaFiscal(id, data, 1, NULL); /*Printando os dados da Nota e de seus respectivos itens*/

            }else{
                criaTXT(&arq); /*Criando arquivo .txt*/

                if(arq!=NULL){
                    fprintf(arq,"\n--------------------------------------------------\n");
                    fprintf(arq,"--- LOUCO DAS PEDRAS - PRODUTOS FARMACOLÓGICOS ---");
                    fprintf(arq,"\n--------------------------------------------------\n");

                    fprintf(arq,"\n-------- Compras efetuadas por um Cliente --------\n");

                    fprintf(arq,"\n\tData Específico: %s", data);

                    getNomeCliente(id, nome); /*Pegando o nome do cliente*/
                    fprintf(arq,"\n\n\tID Cliente: %lu\n\tNome: %s", id, nome);

                    fprintf(arq,"\n\n--------------------------------------------------\n");
                    fprintf(arq,"--------------- Notas e seus Itens ---------------\n");
                    verificaClienteDataNotaFiscal(id, data, 1, arq); /*Printando os dados das Notas e de seus respectivos itens*/

                    fclose(arq);
                    printf("\n\t--- Arquivo criado com sucesso!! ---");
                }else
                    printf("\n\tNão foi possível criar o arquivo! Operação cancelada!\n");
            }
        }else
            printf("\n\t--- Nota Fiscal não encontrada ---");
    }else
        printf("\n\t--- Cliente não encontrado ---");
}

void relatorioComprasClienteIntervalo(int tipo){
    int valido;
    char nome[100], dataMenor[11], dataMaior[11];
    unsigned long id;
    FILE *arq = NULL;

    printf("\n---------------------------------------------------------\n");
    printf("- Compras efetuadas por um Cliente - Intervalo de Datas -");
    printf("\n---------------------------------------------------------\n");

    printf("\n\tForneça o ID do Cliente: ");
    setbuf(stdin, NULL);
    scanf("%lu", &id);

    abrirArquivo(&arq, "cliente.dat");
    valido = pesquisaClienteID(arq, id); /*Verifica se o cliente existe*/
    fclose(arq);

    if(valido!=-1){
        printf("\n\t-- Data Menor --"); /*Entrada das datas (intervalo)*/
        entradaData(dataMenor);
        printf("\n\t-- Data Maior --");
        entradaData(dataMaior);

        valido = verificaClienteIntervaloNotaFiscal(id, dataMenor, dataMaior, 0, NULL); /*Verifica se existem notas que correspondem às duas condições do relatório: id do cliente e intervalo de datas*/

        if(valido){
            if(tipo==1){  /*Tipo de impressão*/
                printLogo();
                printf("\n-------- Compras efetuadas por um Cliente --------\n");

                printf("\n\tIntervalo de Datas: %s - %s", dataMenor, dataMaior);

                getNomeCliente(id, nome); /*Pegando o nome do cliente*/
                printf("\n\n\tID Cliente: %lu\n\tNome: %s", id, nome);

                printf("\n\n--------------------------------------------------\n");
                printf("--------------- Notas e seus Itens ---------------\n");
                verificaClienteIntervaloNotaFiscal(id, dataMenor, dataMaior, 1, NULL); /*Printando os dados das Notas e de seus respectivos itens*/

            }else{
                criaTXT(&arq); /*Criando arquivo .txt*/

                if(arq!=NULL){
                    fprintf(arq,"\n--------------------------------------------------\n");
                    fprintf(arq,"--- LOUCO DAS PEDRAS - PRODUTOS FARMACOLÓGICOS ---");
                    fprintf(arq,"\n--------------------------------------------------\n");

                    fprintf(arq,"\n-------- Compras efetuadas por um Cliente --------\n");

                    getNomeCliente(id, nome); /*Pegando o nome do cliente*/
                    fprintf(arq,"\n\tIntervalo de Datas: %s - %s", dataMenor, dataMaior);

                    fprintf(arq,"\n\n\tID Cliente: %lu\n\tNome: %s", id, nome);

                    fprintf(arq,"\n\n--------------------------------------------------\n");
                    fprintf(arq,"--------------- Notas e seus Itens ---------------\n");
                    verificaClienteIntervaloNotaFiscal(id, dataMenor, dataMaior, 1, arq); /*Printando os dados das Notas e de seus respectivos itens*/

                    fclose(arq);
                    printf("\n\t--- Arquivo criado com sucesso!! ---");
                }else
                    printf("\n\tNão foi possível criar o arquivo! Operação cancelada!\n");
            }
        }else
            printf("\n\t--- Nota Fiscal não encontrada ---");
    }else
        printf("\n\t--- Cliente não encontrado ---");
}


void relatorioVendasVendedorDia(int tipo){
    int valido;
    char nome[100], data[11];
    unsigned long id;
    FILE *arq = NULL;

    printf("\n-----------------------------------------------------\n");
    printf("- Vendas efetuadas por um Vendedor - Dia Específico -");
    printf("\n-----------------------------------------------------\n");

    printf("\n\tForneça o ID do Vendedor: ");
    setbuf(stdin, NULL);
    scanf("%lu", &id);

    abrirArquivo(&arq, "vendedor.dat");
    valido = pesquisaVendID(arq, id); /*Verifica se o vendedor existe*/
    fclose(arq);

    if(valido!=-1){
        entradaData(data); /*Entrada da data*/
        valido = verificaVendDataNotaFiscal(id, data, 0, 0, NULL); /*Verifica se existem notas que correspondem às duas condições do relatório: id do cliente e data*/

        if(valido){
            if(tipo==1){ /*Tipo de impressão*/
                printLogo();
                printf("\n-------- Vendas efetuadas por um Vendedor --------\n");

                printf("\n\tDia Específico: %s", data);

                getNomeVendedor(id, nome); /*Pegando o nome do vendedor*/
                printf("\n\n\tID Vendedor: %lu\n\tNome: %s", id, nome);

                printf("\n\n--------------------------------------------------\n");
                printf("--------------- Notas e seus Itens ---------------\n");
                verificaVendDataNotaFiscal(id, data, 1, 0, NULL); /*Printando os dados das Notas e de seus respectivos itens*/

            }else{
                criaTXT(&arq);

                if(arq!=NULL){
                    fprintf(arq,"\n--------------------------------------------------\n");
                    fprintf(arq,"--- LOUCO DAS PEDRAS - PRODUTOS FARMACOLÓGICOS ---");
                    fprintf(arq,"\n--------------------------------------------------\n");

                    fprintf(arq,"\n-------- Vendas efetuadas por um Vendedor --------\n");

                    fprintf(arq,"\n\tDia Específico: %s", data);

                    getNomeVendedor(id, nome);
                    fprintf(arq,"\n\n\tID Vendedor: %lu\n\tNome: %s", id, nome);

                    fprintf(arq,"\n\n--------------------------------------------------\n");
                    fprintf(arq,"--------------- Notas e seus Itens ---------------\n");
                    verificaVendDataNotaFiscal(id, data, 1, 0, arq); /*Printando os dados das Notas e de seus respectivos itens*/

                    fclose(arq);
                    printf("\n\t--- Arquivo criado com sucesso!! ---");
                }else
                    printf("\n\tNão foi possível criar o arquivo! Operação cancelada!\n");
            }
        }else
            printf("\n\t--- Nota Fiscal não encontrada ---");
    }else
        printf("\n\t--- Vendedor não encontrado ---");
}

void relatorioVendasVendedorMes(int tipo){
    int valido, mes;
    char nome[100];
    unsigned long id;
    FILE *arq = NULL;

    printf("\n------------------------------------------------------\n");
    printf("------- Vendas efetuadas por um Vendedor - Mês -------");
    printf("\n------------------------------------------------------\n");

    printf("\n\tForneça o ID do Vendedor: ");
    setbuf(stdin, NULL);
    scanf("%lu", &id);

    abrirArquivo(&arq, "vendedor.dat");
    valido = pesquisaVendID(arq, id); /*Verifica se o vendedor existe*/
    fclose(arq);

    if(valido!=-1){
        do{
            printf("\n\tForneça o mês (1-12): "); /*Entrada do mês*/
            scanf("%d", &mes);

            if(mes<1 || mes>12)
                printInvOption("Mês");
        }while(mes<1 || mes>12);

        valido = verificaVendDataNotaFiscal(id, "NULL", 0, mes, NULL); /*Verifica se existem notas que correspondem às duas condições do relatório: id do cliente e mês escolhido*/

        if(valido){
            if(tipo==1){ /*Tipo de impressão*/
                printLogo();
                printf("\n-------- Vendas efetuadas por um Vendedor --------\n");

                getNomeMes(mes, nome); /*Pegando o nome do mês*/
                printf("\n\tMês : %s", nome);

                getNomeVendedor(id, nome); /*Pegando o nome do vendedor*/
                printf("\n\n\tID Vendedor: %lu\n\tNome: %s", id, nome);

                printf("\n\n--------------------------------------------------\n");
                printf("--------------- Notas e seus Itens ---------------\n");
                verificaVendDataNotaFiscal(id, "NULL", 1, mes, NULL); /*Printando os dados das Notas e de seus respectivos itens*/

            }else{
                criaTXT(&arq); /*Cria o arquivo .txt*/

                if(arq!=NULL){
                    fprintf(arq,"\n--------------------------------------------------\n");
                    fprintf(arq,"--- LOUCO DAS PEDRAS - PRODUTOS FARMACOLÓGICOS ---");
                    fprintf(arq,"\n--------------------------------------------------\n");

                    fprintf(arq,"\n-------- Vendas efetuadas por um Vendedor --------\n");

                    getNomeMes(mes, nome);
                    fprintf(arq,"\n\tMês : %s", nome);

                    getNomeVendedor(id, nome);
                    fprintf(arq,"\n\n\tID Vendedor: %lu\n\tNome: %s", id, nome);

                    fprintf(arq,"\n\n--------------------------------------------------\n");
                    fprintf(arq,"--------------- Notas e seus Itens ---------------\n");
                    verificaVendDataNotaFiscal(id, "NULL", 1, mes, arq); /*Printando os dados das Notas e de seus respectivos itens*/

                    fclose(arq);
                    printf("\n\t--- Arquivo criado com sucesso!! ---");
                }else
                    printf("\n\tNão foi possível criar o arquivo! Operação cancelada!\n");
            }
        }else
            printf("\n\t--- Nota Fiscal não encontrada ---");
    }else
        printf("\n\t--- Vendedor não encontrado ---");
}


void relatorioMaiorValorVendedorMes(int tipo){
    int mes;
    float maiorVal;
    char nome[100];
    FILE *arq = NULL;

    printf("\n----------------------------------------------------\n");
    printf("--- Vendedor(es) com maior valor em Vendas - Mês ---");
    printf("\n----------------------------------------------------\n");

    do{
        printf("\n\tForneça o mês (1-12): "); /*Entrada do mês*/
        scanf("%d", &mes);

        if(mes<1 || mes>12)
            printInvOption("Mês");
    }while(mes<1 || mes>12);

    maiorVal = verificaMaiorValorVendas(mes, "NULL", "NULL"); /*Verifica se existem notas emitidas no mês selecionado*/

    if(maiorVal>0){
        if(tipo==1){ /*Tipo de impressão*/
            printLogo();
            printf("\n----- Vendedor(es) com maior valor em Vendas -----\n");

            getNomeMes(mes, nome); /*Pegando o nome do mês*/
            printf("\n\tMês : %s", nome);
            printf("\n\tMaior Valor : R$%.2f", maiorVal);

            printf("\n--------------------------------------------------\n");
            printaVendMaiorValorVendas(maiorVal, mes, "NULL", "NULL", NULL); /*Printando os dados do Vendedor(es) com maior valor em vendas*/
        }else{
            criaTXT(&arq);

            if(arq!=NULL){
                fprintf(arq,"\n--------------------------------------------------\n");
                fprintf(arq,"--- LOUCO DAS PEDRAS - PRODUTOS FARMACOLÓGICOS ---");
                fprintf(arq,"\n--------------------------------------------------\n");

                fprintf(arq,"\n----- Vendedor(es) com maior valor em Vendas -----\n");

                getNomeMes(mes, nome); /*Pegando o nome do mês*/
                fprintf(arq,"\n\tMês : %s", nome);
                fprintf(arq,"\n\tMaior Valor : R$%.2f", maiorVal);

                fprintf(arq,"\n--------------------------------------------------\n");
                printaVendMaiorValorVendas(maiorVal, mes, "NULL", "NULL", arq); /*Printando os dados do Vendedor(es) com maior valor em vendas*/
                fprintf(arq,"\n--------------------------------------------------\n");

                fclose(arq);
                printf("\n\t--- Arquivo criado com sucesso!! ---");
            }else
                printf("\n\tNão foi possível criar o arquivo! Operação cancelada!\n");
        }
    }else
        printf("\n\t--- Nota Fiscal não encontrada ---");
}

void relatorioMaiorValorVendedorIntervalo(int tipo){
    float maiorVal;
    char dataMaior[11], dataMenor[11];
    FILE *arq = NULL;

    printf("\n---------------------------------------------------------------\n");
    printf("- Vendedor(es) com maior valor em Vendas - Intervalo de Datas -");
    printf("\n---------------------------------------------------------------\n");

    printf("\n\t-- Data Menor --"); /*Entrada das datas (intervalo)*/
    entradaData(dataMenor);
    printf("\n\t-- Data Maior --");
    entradaData(dataMaior);

    maiorVal = verificaMaiorValorVendas(0, dataMenor, dataMaior); /*Verifica se existem notas emitidas entre o intervalo das datas selecionadas*/

    if(maiorVal>0){
        if(tipo==1){ /*Tipo de impressão*/
            printLogo();
            printf("\n----- Vendedor(es) com maior valor em Vendas -----\n");

            printf("\n\tIntervalo de Datas: %s - %s", dataMenor, dataMaior);
            printf("\n\tMaior Valor : R$%.2f", maiorVal);

            printf("\n\n--------------------------------------------------\n");
            printaVendMaiorValorVendas(maiorVal, 0, dataMenor, dataMaior, NULL); /*Printando os dados do Vendedor(es) com maior valor em vendas*/
        }else{
            criaTXT(&arq); /*Criando o arquivo .txt*/

            if(arq!=NULL){
                fprintf(arq,"\n--------------------------------------------------\n");
                fprintf(arq,"--- LOUCO DAS PEDRAS - PRODUTOS FARMACOLÓGICOS ---");
                fprintf(arq,"\n--------------------------------------------------\n");

                fprintf(arq,"\n----- Vendedor(es) com maior valor em Vendas -----\n");

                fprintf(arq,"\n\tIntervalo de Datas: %s - %s", dataMenor, dataMaior);
                fprintf(arq,"\n\tMaior Valor : R$%.2f", maiorVal);

                fprintf(arq,"\n\n--------------------------------------------------\n");
                printaVendMaiorValorVendas(maiorVal, 0, dataMenor, dataMaior, arq); /*Printando os dados do Vendedor(es) com maior valor em vendas*/
                fprintf(arq,"\n\n--------------------------------------------------\n");

                fclose(arq);
                printf("\n\t--- Arquivo criado com sucesso!! ---");
            }else
                printf("\n\tNão foi possível criar o arquivo! Operação cancelada!\n");
        }
    }else
        printf("\n\t--- Nota Fiscal não encontrada ---");
}


void relatorioHistorico(int tipo){
    int valido;
    char nome[100];
    unsigned long id;
    FILE *arq = NULL;

    printf("\n---------------------------------------------------\n");
    printf("----------- Histórico de Valor de Venda -----------");
    printf("\n---------------------------------------------------\n");

    printf("\n\tForneça o ID do Produto: ");
    scanf("%lu", &id);

    abrirArquivo(&arq, "produto.dat");
    valido = pesquisaProdutoID(arq, id); /*Verifica se o produto existe*/
    fclose(arq);

    if(valido!=-1){
         valido = printaHistorico(arq, id, 0); /*Verifica se há histórico*/

         if(valido) {
            if(tipo==1){ /*Tipo de impressão*/
                printLogo();
                printf("\n----------- Histórico de Valor de Venda ----------\n");

                getNomeProduto(id, nome);
                printf("\n\tID Produto: %lu\n\tNome: %s", id, nome);
                printf("\n\t----------------------------------------");

                printaHistorico(NULL, id, 1); /*Printando todo o histórico*/
            }else{
                criaTXT(&arq);

                if(arq!=NULL){
                    fprintf(arq,"\n--------------------------------------------------\n");
                    fprintf(arq,"--- LOUCO DAS PEDRAS - PRODUTOS FARMACOLÓGICOS ---");
                    fprintf(arq,"\n--------------------------------------------------\n");

                    fprintf(arq, "\n----------- Histórico de Valor de Venda ----------\n");

                    getNomeProduto(id, nome);
                    fprintf(arq, "\n\tID Produto: %lu\n\tNome: %s", id, nome);
                    fprintf(arq, "\n\t----------------------------------------");

                    printaHistorico(arq, id, 1); /*Printando todo o histórico*/

                    fclose(arq);
                    printf("\n\t--- Arquivo criado com sucesso!! ---");
                }else
                    printf("\n\tNão foi possível criar o arquivo! Operação cancelada!\n");
            }
         }else
            printf("\n\t--- O produto não possui histórico ---");

    }else
        printf("\n\t--- Produto não encontrado ---");
}


/*====================================================================================================*/
void criaTXT(FILE **arq){
    int valido;
    char nome[100];

    do{
        printf("\n\tForneça o nome para o arquivo (sem extensão): ");
        setbuf(stdin, NULL);
        fgets(nome, 100, stdin);

        valido = retiraEnter(nome);
        if(valido)
            printf("\n\tNome vazio! Tente novamente!");
        else
            strcat(nome,".txt"); /*Adicionando a extensão*/
    }while(valido);

    *arq = fopen(nome, "r+"); /*Tentando criar/abrir o arquivo*/
    if(*arq==NULL)
        *arq = fopen(nome, "w+");
}

void getNomeMes(int mes, char *nomeMes){
    char meses[12][50]={"Janeiro","Fevereiro","Março","Abril","Maio","Junho","Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};
    strcpy(nomeMes,meses[mes-1]);
}

