#include <stdio.h>
#include <string.h>
#include "fornecedor.h"
#include "funcGerais.h"
#include "entradaSaida.h"

/*=======================MENU=======================*/
void areaFornecedor(){
    int op, inv;
    FILE *arq;

	abrirArquivo(&arq, "fornecedor.dat");

    if(arq!=NULL){
        do{
            printf("\n---------------------------------------------------\n");
            printf("----------- Manutenção dos Fornecedores -----------");
            printf("\n---------------------------------------------------\n");
            printf("\n\t1 - Cadastro");
            printf("\n\t2 - Alteração");
            printf("\n\t3 - Consulta");
            printf("\n\t4 - Listagem");
            printf("\n\t5 - Voltar ao Menu Principal\n");

            do{
                printf("\n\tEscolha uma opção: ");
                scanf("%d", &op);

                inv = 0;
                switch(op){
                case 1:
                    cadastroFornc(arq);
                    break;
                case 2:
                    menuAlterarFornc(arq);
                    break;
                case 3:
                    menuConsultaFornc(arq);
                    break;
                case 4:
                    listagemFornc(arq);
                    break;
                case 5:
                    break;
                default:
                    inv = 1;
                }

                if(inv)
                    printInvOption("Opção");

            }while(inv);
        }while (op != 5);

        fclose(arq);
    }else
        printf("\n\tErro na abertura do arquivo!!!\n");

}


/*=======================CADASTRO=======================*/
void cadastroFornc(FILE *arq){
    int sair;
    TFornecedor fornc;

    do{
        printf("\n---------------------------------------------------\n");
        printf("--------------- Cadastro Fornecedor ---------------");
        printf("\n---------------------------------------------------\n");

        printf("\n\t--Forneça os dados do novo fornecedor--\n");
        fornc.id = novoIdFornc(arq); /*Gera um novo ID*/
        printf("\n\tID: %lu", fornc.id);

        do{
            entradaNome(fornc.nome);
            sair = pesquisaForncNome(arq, fornc.nome); /*Verifica se o nome é repetido*/

            if(sair != -1)
                printf("\n\tO Nome fornecido pertence a outro fornecedor!! Tente novamente\n");
        }while(sair != -1);

        do{
            entradaCNPJ(fornc.cnpj);
            sair = pesquisaForncCNPJ(arq, fornc.cnpj); /*Verifica se o CNPJ é repetido*/

            if(sair != -1)
                printf("\n\tO CNPJ fornecido pertence a outro fornecedor!! Tente novamente\n");
        }while(sair != -1);

        entradaEmail(fornc.email);
        entradaTelefone(fornc.telefone);

        fseek(arq, sizeof(TFornecedor)*(fornc.id-1), SEEK_SET); /*Posiciona o apontador e armazena os dados do novo cliente*/
        fwrite(&fornc, sizeof(TFornecedor), 1, arq);

        printf("\n--------- Fornecedor Cadastrado com Sucesso ---------\n");

        printf("\n\tDeseja abandonar o cadastro?");
        escolhaSimNao(&sair);

    }while(sair!=1);
}

unsigned long novoIdFornc(FILE *arq){
    unsigned long quantidade = 0;
    TFornecedor f;

    fseek(arq, 0, SEEK_SET);

    while(fread(&f, sizeof(TFornecedor), 1, arq)==1)
        if(f.id != 0) /*Verifica se o fornecedor dessa posição foi excluído*/
            quantidade++;
        else
            return quantidade+1;

    return quantidade+1;
}


/*=======================ALTERAÇÃO=======================*/
void menuAlterarFornc(FILE *arq){
    int op, valido;

    fseek(arq, 0, SEEK_END);
    if(ftell(arq)>0){
        do{
            printf("\n----------------------------------------------------\n");
            printf("--------------- Alteração Fornecedor ---------------");
            printf("\n----------------------------------------------------\n");

            do{
                printf("\n\t1 - Alterar\n\t2 - Excluir\n\t3 - Voltar");
                printf("\n\tEscolha uma opção: ");
                scanf("%d", &op);

                valido = 0;
                switch(op){
                case 1:
                    alterarFornc(arq);
                    break;
                case 2:
                    excluirFornc(arq);
                    break;
                case 3:
                    break;
                default:
                    printInvOption("Opção");
                    valido=1;
                    break;
                }
            }while(valido);

        }while(op!=3);
    }else
        printf("\n\tNenhum forncedor cadastrado!!\n");
}

void alterarFornc(FILE *arq){
    int posicao, sair, op;
    TFornecedor fornc;

    posicao = consultaForncID(arq);
    fseek(arq, sizeof(TFornecedor)*posicao,SEEK_SET); /*Recebe os dados do fornecedor*/
    fread(&fornc, sizeof(TFornecedor), 1, arq);

    if(posicao!=-1){
        printf("\t-----------------------------------------");
        printf("\n\n\tDeseja prosseguir com a alteração?"); /*Confirmando a alteração*/
        escolhaSimNao(&op);
        if(op==1){
            printf("\n\t-- Forneça os novos dados do fornecedor --\n");

            printf("\n\n\tDeseja alterar o nome do fornecedor?");
            escolhaSimNao(&op);
            if(op==1)
                do{
                    entradaNome(fornc.nome);
                    sair = pesquisaForncNome(arq, fornc.nome);

                    if(sair != -1)
                        printf("\n\tO Nome fornecido pertence a outro fornecedor!! Tente novamente\n");
                }while(sair != -1);

            printf("\n\n\tDeseja alterar o email do fornecedor?");
            escolhaSimNao(&op);
            if(op==1)
                entradaEmail(fornc.email);

            printf("\n\n\tDeseja alterar o telefone do fornecedor?");
            escolhaSimNao(&op);
            if(op==1)
                entradaTelefone(fornc.telefone);

            fseek(arq, sizeof(TFornecedor)*posicao,SEEK_SET); /*Armazenando os dados atualizados*/
            fwrite(&fornc, sizeof(TFornecedor), 1, arq);

            printf("\n--------- Alteração realizada com Sucesso ---------\n");
        }else
            printf("\n-------------- Alteração Cancelada --------------\n");
    }
}

void excluirFornc(FILE *arq){
    int posicao = 0, op;
    unsigned long id;
    TFornecedor fornc;

    /*Permitindo uma listagem prévia de todos os fornecedores, caso o usuário tenha se esquecido do ID*/
    printf("\n-------------------- ATENÇÃO --------------------\n");
    printf("\n\tEsta operação é realizada utilizando o ID!\n\tDeseja realizar uma listagem dos fornecedores?");
    escolhaSimNao(&op);
    if(op==1)
        listagemFornc(arq);

    printf("\n\tForneça o id:");
    scanf("%lu", &id);

    fseek(arq, 0, SEEK_SET);

    while(fread(&fornc, sizeof(TFornecedor), 1, arq)==1)
        if(fornc.id==id)
            break;
        else
            posicao++;

    if(fornc.id==id){
        fseek(arq, posicao*sizeof(TFornecedor), SEEK_SET);
        fread(&fornc, sizeof(TFornecedor), 1, arq);

        printf("\n\t-- Dados do Fornecedor --\n");
        printTFornc(fornc);

        printf("\t-----------------------------------------");
        printf("\n\n\tDeseja prosseguir com a exclusão?"); /*Confirmando a exclusão*/
        escolhaSimNao(&op);
        if(op==1){
            fornc.id = 0;
            strcpy(fornc.nome, "0\0");
            strcpy(fornc.cnpj, "0\0");
            strcpy(fornc.email, "0\0");
            strcpy(fornc.telefone, "0\0");

            fseek(arq, sizeof(TFornecedor)*posicao,SEEK_SET);
            fwrite(&fornc, sizeof(TFornecedor), 1, arq);

            printf("\n--------- Exclusão realizada com sucesso ---------\n");
        }else
            printf("\n--------------- Exclusão cancelada ---------------\n");

    }else
        printf("\n\tFornecedor inexistente!!!\n");
}


/*=======================CONSULTA=======================*/
void menuConsultaFornc(FILE *arq){
    int op, valido;

    fseek(arq, 0, SEEK_END);
    if(ftell(arq)>0){
        do{
            printf("\n---------------------------------------------------\n");
            printf("--------------- Consulta Fornecedor ---------------");
            printf("\n---------------------------------------------------\n");

            do{
                printf("\n\t1 - ID\n\t2 - CNPJ\n\t3 - Prefixo do Nome\n\t4 - Voltar");
                printf("\n\tEscolha uma opção: ");
                scanf("%d", &op);

                valido = 0;
                switch(op){
                case 1:
                    consultaForncID(arq);
                    break;
                case 2:
                    consultaForncCNPJ(arq);
                    break;
                case 3:
                    consultaForncNome(arq);
                    break;
                case 4:
                    break;
                default:
                    printInvOption("Opção");
                    valido=1;
                    break;
                }
            }while(valido);

        }while(op!=4);
    }else
        printf("\n\tNenhum fornecedor cadastrado!!\n");
}

int consultaForncID(FILE *arq){
    unsigned long id;
    int posicao, op;
    TFornecedor fornc;

    /*Permitindo uma listagem prévia de todos os fornecedores, caso o usuário tenha se esquecido do ID*/
    printf("\n-------------------- ATENÇÃO --------------------\n");
    printf("\n\tEsta operação é realizada utilizando o ID!\n\tDeseja realizar uma listagem dos fornecedores?");
    escolhaSimNao(&op);
    if(op==1)
        listagemFornc(arq);

    printf("\n\tForneça o id: ");
    scanf("%lu", &id);

    posicao = pesquisaForncID(arq, id);
    if(posicao!=-1){
        fseek(arq, posicao*sizeof(TFornecedor), SEEK_SET);
        fread(&fornc, sizeof(TFornecedor), 1, arq);

        printf("\n\t-- Dados do Fornecedor --\n");
        printTFornc(fornc);
    }else
        printf("\n\tFornecedor inexistente!!!\n");

    return posicao;
}

void consultaForncCNPJ(FILE *arq){
    char cnpj[15];
    int posicao;
    TFornecedor fornc;

    printf("\n\tForneça o CNPJ: ");
    setbuf(stdin, NULL);
    fgets(cnpj, 15, stdin);

    retiraEnter(cnpj);

    posicao = pesquisaForncCNPJ(arq, cnpj);
    if(posicao!=-1){
        fseek(arq, posicao*sizeof(TFornecedor), SEEK_SET);
        fread(&fornc, sizeof(TFornecedor), 1, arq);

        printf("\n\t-- Dados do Fornecedor --\n");
        printTFornc(fornc);
    }else
        printf("\n\tFornecedor inexistente!!!\n");
}

void consultaForncNome(FILE *arq){
    char nome[11];
    int achou=0;
    TFornecedor fornc;

    printf("\n\tForneça o prefixo(max 10 caracteres): ");
    setbuf(stdin, NULL);
    fgets(nome, 11, stdin);

    retiraEnter(nome);
    padronizaNome(nome);

    fseek(arq, 0, SEEK_SET);
    while(fread(&fornc, sizeof(TFornecedor), 1, arq)==1){
        if(strncmp(nome,fornc.nome,strlen(nome))==0){ /*Comprara o prefixo com o nome*/
            if(!achou)
                printf("\n\t-- Dados dos Fornecedores --\n");

            printTFornc(fornc);
            achou = 1;
        }
    }

    if(!achou)
        printf("\n\tVendedor inexistente!!!\n");
}


/*=======================LISTAGEM=======================*/
void listagemFornc(FILE *arq){
    int qtde=0;
    TFornecedor fornc;

    printf("\n---------------------------------------------------\n");
    printf("--------------- Listagem Fornecedores ---------------");
    printf("\n---------------------------------------------------\n");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq) > 0){
        fseek(arq, 0, SEEK_SET);
        while(fread(&fornc, sizeof(TFornecedor), 1, arq)==1) /*Printa os dados recebidos enquanto fread retornar 1*/
            if(fornc.id != 0){
                printTFornc(fornc);
                printf("\t-----------------------------------------");
                qtde=1;
            }

        if(!qtde)
            printf("\n\tNenhum fornecedor cadastrado!!\n");
    }else
        printf("\n\tNenhum fornecedor cadastrado!!\n");
}


int pesquisaForncID(FILE *arq, unsigned long id){
    int posicao = 0;
    TFornecedor f;

    fseek(arq, 0, SEEK_SET);

    while(fread(&f, sizeof(TFornecedor), 1, arq)==1){
        if(f.id != 0){
            if(f.id==id)
                return posicao;
            else
                posicao++;
        }
    }

    return -1;
}

int pesquisaForncCNPJ(FILE *arq, char *cnpj){
    int posicao = 0;
    TFornecedor f;

    fseek(arq, 0, SEEK_SET);
    while(fread(&f, sizeof(TFornecedor), 1, arq)==1){
        if(strcmp(cnpj, f.cnpj)==0)
            return posicao;
        else
            posicao++;
    }

    return -1;
}

int pesquisaForncNome(FILE *arq, char *nome){
    int posicao = 0;
    TFornecedor f;

    fseek(arq, 0, SEEK_SET);
    while(fread(&f, sizeof(TFornecedor), 1, arq)==1){
        if(strcmp(nome, f.nome)==0)
            return posicao;
        else
            posicao++;
    }

    return -1;
}

void printTFornc(TFornecedor fornc){
    printf("\n\tID        = %lu", fornc.id);
    printf("\n\tNome      = %s", fornc.nome);
    printf("\n\tCNPJ      = %s", fornc.cnpj);
    printf("\n\tEmail     = %s", fornc.email);
    printf("\n\tTelefone  = %s\n", fornc.telefone);
}

unsigned long getIDFornecedor(FILE *arq, int posicao){
    TFornecedor fornecedor;

    fseek(arq, posicao*sizeof(TFornecedor), SEEK_SET);
    fread(&fornecedor, sizeof(TFornecedor), 1, arq);

    return fornecedor.id;
}

void getNomeFornecedor(unsigned long id, char *nome){
    int posicao;
    TFornecedor fornc;

    FILE *arq;
    abrirArquivo(&arq,"fornecedor.dat");

    posicao = pesquisaForncID(arq, id);
    if(posicao!=-1){
        fseek(arq, sizeof(TFornecedor)*posicao, SEEK_SET);
        fread(&fornc, sizeof(TFornecedor), 1, arq);

        strcpy(nome, fornc.nome);
    }

    fclose(arq);
}


