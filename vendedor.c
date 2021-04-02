#include <stdio.h>
#include <string.h>
#include "vendedor.h"
#include "funcGerais.h"
#include "entradaSaida.h"

/*=======================MENU=======================*/
void areaVendedor(){
    int op, inv;
    FILE *arq;

	abrirArquivo(&arq, "vendedor.dat");

    if(arq!=NULL){
        do{
            printf("\n---------------------------------------------------\n");
            printf("------------ Manutenção dos Vendedores ------------");
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
                    cadastroVend(arq);
                    break;
                case 2:
                    menuAlterarVend(arq);
                    break;
                case 3:
                    menuConsultaVend(arq);
                    break;
                case 4:
                    listagemVend(arq);
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
void cadastroVend(FILE *arq){
    int sair;
    TVendedor vend;

    do{
        printf("\n---------------------------------------------------\n");
        printf("---------------- Cadastro Vendedor ----------------");
        printf("\n---------------------------------------------------\n");

        printf("\n\t--Forneça os dados do novo vendedor--\n");
        vend.id = novoIdVend(arq);
        printf("\n\tID: %lu", vend.id);

        entradaNome(vend.nome);

        do{
            entradaCPF(vend.cpf);
            sair = pesquisaVendCPF(arq, vend.cpf);

            if(sair != -1)
                printf("\n\tO CPF fornecido pertence a outro vendedor!! Tente novamente\n");
        }while(sair != -1);

        do{
            entradaEmail(vend.email);
            sair = pesquisaVendEmail(arq, vend.email);

            if(sair != -1)
                printf("\n\tO Email fornecido pertence a outro vendedor!! Tente novamente\n");
        }while(sair != -1);

        entradaTelefone(vend.telefone);
        entradaSenha(vend.password);

        fseek(arq, sizeof(TVendedor)*(vend.id-1), SEEK_SET);
        fwrite(&vend, sizeof(TVendedor), 1, arq);

        printf("\n--------- Vendedor Cadastrado com Sucesso ---------\n");

        printf("\n\tDeseja abandonar o cadastro?");
        escolhaSimNao(&sair);
    }while(sair!=1);
}

unsigned long novoIdVend(FILE *arq){
    unsigned long quantidade = 0;
    TVendedor v;

    fseek(arq, 0, SEEK_SET);

    while(fread(&v, sizeof(TVendedor), 1, arq)==1)
        if(v.id != 0)
            quantidade++;
        else
            return quantidade+1;

    return quantidade+1;
}


/*=======================ALTERAÇÃO=======================*/
void menuAlterarVend(FILE *arq){
    int op, valido;

    fseek(arq, 0, SEEK_END);
    if(ftell(arq)>0){
        do{
            printf("\n----------------------------------------------------\n");
            printf("---------------- Alteração Vendedor ----------------");
            printf("\n----------------------------------------------------\n");

            do{
                printf("\n\t1 - Alterar\n\t2 - Excluir\n\t3 - Voltar");
                printf("\n\tEscolha uma opção: ");
                scanf("%d", &op);

                valido = 0;
                switch(op){
                case 1:
                    alterarVend(arq);
                    break;
                case 2:
                    excluirVend(arq);
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
        printf("\n\tNenhum vendedor cadastrado!!\n");
}

void alterarVend(FILE *arq){
    int posicao, sair, op;
    TVendedor vend;

    posicao = consultaVendID(arq);
    fseek(arq, sizeof(TVendedor)*posicao,SEEK_SET);
    fread(&vend, sizeof(TVendedor), 1, arq);

    if(posicao!=-1){
        printf("\t-----------------------------------------");
        printf("\n\n\tDeseja prosseguir com a alteração?"); /*Confirmando a alteração*/
        escolhaSimNao(&op);
        if(op==1){
            printf("\n\t-- Forneça os novos dados do vendedor --\n");

            printf("\n\n\tDeseja alterar o nome do vendedor?");
            escolhaSimNao(&op);
            if(op==1)
                entradaNome(vend.nome);

            printf("\n\n\tDeseja alterar o email do vendedor?");
            escolhaSimNao(&op);
            if(op==1)
                do{
                    entradaEmail(vend.email);
                    sair = pesquisaVendEmail(arq, vend.email);

                    if(sair != -1)
                        printf("\n\tO Email fornecido pertence a outro vendedor!! Tente novamente\n");
                }while(sair != -1);

            printf("\n\n\tDeseja alterar o telefone do vendedor?");
            escolhaSimNao(&op);
            if(op==1)
                entradaTelefone(vend.telefone);

            fseek(arq, sizeof(TVendedor)*posicao,SEEK_SET);
            fwrite(&vend, sizeof(TVendedor), 1, arq);

            printf("\n--------- Alteração realizada com Sucesso ---------\n");
        }else
            printf("\n-------------- Alteração Cancelada --------------\n");
    }
}

void excluirVend(FILE *arq){
    int posicao = 0, op;
    unsigned long id;
    TVendedor vend;

    /*Permitindo uma listagem prévia de todos os vendedores, caso o usuário tenha se esquecido do ID*/
    printf("\n-------------------- ATENÇÃO --------------------\n");
    printf("\n\tEsta operação é realizada utilizando o ID!\n\tDeseja realizar uma listagem dos vendedores?");
    escolhaSimNao(&op);
    if(op==1)
        listagemVend(arq);

    printf("\n\tForneça o id:");
    scanf("%lu", &id);

    fseek(arq, 0, SEEK_SET);

    while(fread(&vend, sizeof(TVendedor), 1, arq)==1)
        if(vend.id==id)
            break;
        else
            posicao++;

    if(vend.id==id){
        fseek(arq, posicao*sizeof(TVendedor), SEEK_SET);
        fread(&vend, sizeof(TVendedor), 1, arq);

        printf("\n\t-- Dados do Vendedor --\n");
        printTVend(vend);

        printf("\t-----------------------------------------");
        printf("\n\n\tDeseja prosseguir com a exclusão?"); /*Confirmando a exclusão*/
        escolhaSimNao(&op);
        if(op==1){
            vend.id = 0;
            strcpy(vend.nome, "0\0");
            strcpy(vend.cpf, "0\0");
            strcpy(vend.email, "0\0");
            strcpy(vend.telefone, "0\0");

            fseek(arq, sizeof(TVendedor)*posicao,SEEK_SET);
            fwrite(&vend, sizeof(TVendedor), 1, arq);

            printf("\n--------- Exclusão realizada com sucesso ---------\n");
        }else
            printf("\n--------------- Exclusão cancelada ---------------\n");

    }else
        printf("\n\tVendedor inexistente!!!\n");
}


/*=======================CONSULTA=======================*/
void menuConsultaVend(FILE *arq){
    int op, valido;

    fseek(arq, 0, SEEK_END);
    if(ftell(arq)>0){
        do{
            printf("\n---------------------------------------------------\n");
            printf("---------------- Consulta Vendedor ----------------");
            printf("\n---------------------------------------------------\n");

            do{
                printf("\n\t1 - ID\n\t2 - CPF\n\t3 - Prefixo do Nome\n\t4 - Voltar");
                printf("\n\tEscolha uma opção: ");
                scanf("%d", &op);

                valido = 0;
                switch(op){
                case 1:
                    consultaVendID(arq);
                    break;
                case 2:
                    consultaVendCPF(arq);
                    break;
                case 3:
                    consultaVendNome(arq);
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
        printf("\n\tNenhum vendedor cadastrado!!\n");
}

int consultaVendID(FILE *arq){
    unsigned long id;
    int posicao, op;
    TVendedor vendedor;

    /*Permitindo uma listagem prévia de todos os vendedores, caso o usuário tenha se esquecido do ID*/
    printf("\n-------------------- ATENÇÃO --------------------\n");
    printf("\n\tEsta operação é realizada utilizando o ID!\n\tDeseja realizar uma listagem dos vendedores?");
    escolhaSimNao(&op);
    if(op==1)
        listagemVend(arq);

    printf("\n\tForneça o id: ");
    scanf("%lu", &id);

    posicao = pesquisaVendID(arq, id);
    if(posicao!=-1){
        fseek(arq, posicao*sizeof(TVendedor), SEEK_SET);
        fread(&vendedor, sizeof(TVendedor), 1, arq);

        printf("\n\t-- Dados do vendedor --\n");
        printTVend(vendedor);
    }else
        printf("\n\tVendedor inexistente!!!\n");

    return posicao;
}

unsigned long consultaVendCPF(FILE *arq){
    char cpf[12];
    int posicao;
    TVendedor vend;

    printf("\n\tForneça o CPF: ");
    setbuf(stdin, NULL);
    fgets(cpf, 12, stdin);

    retiraEnter(cpf);

    posicao = pesquisaVendCPF(arq, cpf);
    if(posicao!=-1){
        fseek(arq, posicao*sizeof(TVendedor), SEEK_SET);
        fread(&vend, sizeof(TVendedor), 1, arq);

        printf("\n\t-- Dados do Vendedor --\n");
        printTVend(vend);
        return getIDVendedor(arq, posicao);
    }else
        printf("\n\tVendedor inexistente!!!\n");

    return 0;
}

void consultaVendNome(FILE *arq){
    char nome[11];
    int achou=0;
    TVendedor vend;

    printf("\n\tForneça o prefixo(max 10 caracteres): ");
    setbuf(stdin, NULL);
    fgets(nome, 11, stdin);

    retiraEnter(nome);
    padronizaNome(nome);

    fseek(arq, 0, SEEK_SET);
    while(fread(&vend, sizeof(TVendedor), 1, arq)==1){
        if(strncmp(nome,vend.nome,strlen(nome))==0){
            if(!achou)
                printf("\n\t-- Dados dos Vendedores --\n");

            printTVend(vend);
            achou = 1;
        }
    }

    if(!achou)
        printf("\n\tVendedor inexistente!!!\n");
}


/*=======================LISTAGEM=======================*/
void listagemVend(FILE *arq){
    int qtde=0;
    TVendedor vend;

    printf("\n---------------------------------------------------\n");
    printf("--------------- Listagem Vendedores ---------------");
    printf("\n---------------------------------------------------\n");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq) > 0){
        fseek(arq, 0, SEEK_SET);
        while(fread(&vend, sizeof(TVendedor), 1, arq)==1)
            if(vend.id != 0){
                printTVend(vend);
                printf("\t-----------------------------------------");
                qtde=1;
            }

        if(!qtde)
            printf("\n\tNenhum vendedor cadastrado!!\n");
    }else
        printf("\n\tNenhum vendedor cadastrado!!\n");
}

void printTVend(TVendedor vend){
    printf("\n\tID       = %lu", vend.id);
    printf("\n\tNome     = %s", vend.nome);
    printf("\n\tCPF      = %s", vend.cpf);
    printf("\n\tEmail    = %s", vend.email);
    printf("\n\tTelefone = %s\n", vend.telefone);
}


/*=======================PESQUISA=======================*/
int pesquisaVendID(FILE *arq, unsigned long id){
    int posicao = 0;
    TVendedor v;

    fseek(arq, 0, SEEK_SET);

    while(fread(&v, sizeof(TVendedor), 1, arq)==1){
        if(v.id != 0){
            if(v.id==id)
                return posicao;
            else
                posicao++;
        }
    }

    return -1;
}

int pesquisaVendCPF(FILE *arq, char *cpf){
    int posicao = 0;
    TVendedor v;

    fseek(arq, 0, SEEK_SET);
    while(fread(&v, sizeof(TVendedor), 1, arq)==1){
        if(strcmp(cpf, v.cpf)==0)
            return posicao;
        else
            posicao++;
    }

    return -1;
}

int pesquisaVendEmail(FILE *arq, char *email){
    int posicao = 0;
    TVendedor v;

    fseek(arq, 0, SEEK_SET);
    while(fread(&v, sizeof(TVendedor), 1, arq)==1){
        if(strcmp(email, v.email)==0)
            return posicao;
        else
            posicao++;
    }

    return -1;
}


/*=========================GET=========================*/
unsigned long getIDVendedor(FILE *arq, int posicao){
    TVendedor vendedor;

    fseek(arq, posicao*sizeof(TVendedor), SEEK_SET);
    fread(&vendedor, sizeof(TVendedor), 1, arq);

    return vendedor.id;
}

void getSenhaVendedor(FILE *arq, unsigned long id, char *senha){
    int posicao;
    TVendedor vendedor;

    posicao = pesquisaVendID(arq, id);
    if(posicao!=-1){
        fseek(arq, sizeof(TVendedor)*posicao, SEEK_SET);
        fread(&vendedor, sizeof(TVendedor), 1, arq);

        strcpy(senha, vendedor.password);
    }
}

void getNomeVendedor( unsigned long id, char *nome){
    int posicao;
    TVendedor vendedor;

    FILE *arq;
    abrirArquivo(&arq,"vendedor.dat");

    posicao = pesquisaVendID(arq, id);
    if(posicao!=-1){
        fseek(arq, sizeof(TVendedor)*posicao, SEEK_SET);
        fread(&vendedor, sizeof(TVendedor), 1, arq);

        strcpy(nome, vendedor.nome);
    }

    fclose(arq);
}



