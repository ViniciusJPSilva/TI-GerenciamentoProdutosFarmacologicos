#include <stdio.h>
#include <string.h>
#include "cliente.h"
#include "funcGerais.h"
#include "entradaSaida.h"

/*=======================MENU=======================*/
void areaCliente(){
    int op, inv;
    FILE *arq;

	abrirArquivo(&arq, "cliente.dat");

    if(arq!=NULL){
        do{
            printf("\n---------------------------------------------------\n");
            printf("------------- Manutenção dos Clientes -------------");
            printf("\n---------------------------------------------------\n");
            printf("\n\t1 - Cadastro\n\t2 - Alteração\n\t3 - Consulta\n\t4 - Listagem\n\t5 - Voltar ao Menu Principal\n");

            do{
                printf("\n\tEscolha uma opção: ");
                scanf("%d", &op);

                inv = 0;
                switch(op){
                case 1:
                    cadastroCliente(arq);
                    break;
                case 2:
                    menuAlterarCliente(arq);
                    break;
                case 3:
                    menuConsultaCliente(arq);
                    break;
                case 4:
                    listagemClientes(arq);
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
void cadastroCliente(FILE *arq){
    int sair;
    TCliente cliente;

    do{
        printf("\n--------------------------------------------------\n");
        printf("---------------- Cadastro Cliente ----------------");
        printf("\n--------------------------------------------------\n");

        printf("\n\t--Forneça os dados do novo cliente--\n");
        cliente.id = novoIdCliente(arq); /*Gera um novo ID*/
        printf("\n\tID: %lu", cliente.id);

        entradaNome(cliente.nome);

        do{
            entradaCPF(cliente.cpf);
            sair = pesquisaClienteCPF(arq, cliente.cpf); /*Verifica se o CPF é repetido*/

            if(sair != -1)
                printf("\n\tO CPF fornecido pertence a outro cliente!! Tente novamente\n");
        }while(sair != -1);

        entradaEmail(cliente.email);
        entradaTelefone(cliente.telefone);

        fseek(arq, sizeof(TCliente)*(cliente.id-1), SEEK_SET); /*Posiciona o apontador e armazena os dados do novo cliente*/
        fwrite(&cliente, sizeof(TCliente), 1, arq);

        printf("\n--------- Cliente Cadastrado com Sucesso ---------\n");

        printf("\n\tDeseja abandonar o cadastro?");
        escolhaSimNao(&sair);
    }while(sair!=1);
}

unsigned long novoIdCliente(FILE *arq){
    unsigned long quantidade = 0;
    TCliente c;

    fseek(arq, 0, SEEK_SET);
    while(fread(&c, sizeof(TCliente), 1, arq)==1)
        if(c.id != 0) /*Verifica se o cliente dessa posição foi excluído*/
            quantidade++;
        else
            return quantidade+1;

    return quantidade+1;
}


/*=======================ALTERAÇÃO=======================*/
void menuAlterarCliente(FILE *arq){
    int op, valido;

    fseek(arq, 0, SEEK_END);
    if(ftell(arq)>0){
        do{
            printf("\n--------------------------------------------------\n");
            printf("---------------- Alteração Cliente ----------------");
            printf("\n--------------------------------------------------\n");

            do{
                printf("\n\t1 - Alterar\n\t2 - Excluir\n\t3 - Voltar");
                printf("\n\tEscolha uma opção: ");
                scanf("%d", &op);

                valido = 0;
                switch(op){
                case 1:
                    alterarCliente(arq);
                    break;
                case 2:
                    excluirCliente(arq);
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
        printf("\n\tNenhum cliente cadastrado!!\n");
}

void alterarCliente(FILE *arq){
    int posicao, op;
    TCliente cliente;

    posicao = consultaClienteID(arq);
    fseek(arq, sizeof(TCliente)*posicao,SEEK_SET); /*Recebe os dados do cliente*/
    fread(&cliente, sizeof(TCliente), 1, arq);

    if(posicao!=-1){
        printf("\t-----------------------------------------");
        printf("\n\n\tDeseja prosseguir com a alteração?"); /*Confirmando a alteração*/
        escolhaSimNao(&op);
        if(op==1){
            printf("\n\t-- Forneça os novos dados do novo cliente --\n");

            printf("\n\n\tDeseja alterar o nome do cliente?");
            escolhaSimNao(&op);
            if(op==1)
                entradaNome(cliente.nome);

            printf("\n\n\tDeseja alterar o email do cliente?");
            escolhaSimNao(&op);
            if(op==1)
                entradaEmail(cliente.email);

            printf("\n\n\tDeseja alterar o telefone do cliente?");
            escolhaSimNao(&op);
            if(op==1)
                entradaTelefone(cliente.telefone);

            fseek(arq, sizeof(TCliente)*posicao,SEEK_SET); /*Armazenando os dados atualizados*/
            fwrite(&cliente, sizeof(TCliente), 1, arq);

            printf("\n--------- Alteração realizada com Sucesso ---------\n");
        }else
            printf("\n-------------- Alteração Cancelada --------------\n");
    }
}

void excluirCliente(FILE *arq){
    int posicao = 0, op;
    unsigned long id;
    TCliente cliente;

    /*Permitindo uma listagem prévia de todos os clientes, caso o usuário tenha se esquecido do ID*/
    printf("\n-------------------- ATENÇÃO --------------------\n");
    printf("\n\tEsta operação é realizada utilizando o ID!\n\tDeseja realizar uma listagem dos clientes?");
    escolhaSimNao(&op);
    if(op==1)
        listagemClientes(arq);

    /*O sistema de exclusão não utiliza as demais funções pois ele considera os clientes com ID = 0*/
    printf("\n\tForneça o id: ");
    scanf("%lu", &id);

    fseek(arq, 0, SEEK_SET);

    while(fread(&cliente, sizeof(TCliente), 1, arq)==1)
        if(cliente.id==id)
            break;
        else
            posicao++;

    if(cliente.id==id){
        fseek(arq, posicao*sizeof(TCliente), SEEK_SET);
        fread(&cliente, sizeof(TCliente), 1, arq);

        printf("\n\t-- Dados do Cliente --\n");
        printTCliente(cliente);

        printf("\t-----------------------------------------");
        printf("\n\n\tDeseja prosseguir com a exclusão?"); /*Confirmando a exclusão*/
        escolhaSimNao(&op);
        if(op==1){
            cliente.id = 0;
            strcpy(cliente.nome, "0\0");
            strcpy(cliente.cpf, "0\0");
            strcpy(cliente.email, "0\0");
            strcpy(cliente.telefone, "0\0");

            fseek(arq, sizeof(TCliente)*posicao,SEEK_SET);
            fwrite(&cliente, sizeof(TCliente), 1, arq);

            printf("\n--------- Exclusão realizada com sucesso ---------\n");
        }else
            printf("\n--------------- Exclusão cancelada ---------------\n");

    }else
        printf("\n\tCliente inexistente!!!\n");
}


/*=======================CONSULTA=======================*/
void menuConsultaCliente(FILE *arq){
    int op, valido;

    fseek(arq, 0, SEEK_END);
    if(ftell(arq)>0){
        do{
            printf("\n--------------------------------------------------\n");
            printf("---------------- Consulta Cliente ----------------");
            printf("\n--------------------------------------------------\n");

            do{
                printf("\n\t1 - ID\n\t2 - CPF\n\t3 - Prefixo do Nome\n\t4 - Voltar");
                printf("\n\tEscolha uma opção: ");
                scanf("%d", &op);

                valido = 0;
                switch(op){
                case 1:
                    consultaClienteID(arq);
                    break;
                case 2:
                    consultaClienteCPF(arq);
                    break;
                case 3:
                    consultaClienteNome(arq);
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
        printf("\n\tNenhum cliente cadastrado!!\n");
}

int consultaClienteID(FILE *arq){
    unsigned long id;
    int posicao, op;
    TCliente cliente;

    /*Permitindo uma listagem prévia de todos os clientes, caso o usuário tenha se esquecido do ID*/
    printf("\n-------------------- ATENÇÃO --------------------\n");
    printf("\n\tEsta operação é realizada utilizando o ID!\n\tDeseja realizar uma listagem dos clientes?");
    escolhaSimNao(&op);
    if(op==1)
        listagemClientes(arq);

    printf("\n\n\tForneça o id: ");
    scanf("%lu", &id);

    posicao = pesquisaClienteID(arq, id);
    if(posicao!=-1){
        fseek(arq, posicao*sizeof(TCliente), SEEK_SET);
        fread(&cliente, sizeof(TCliente), 1, arq);

        printf("\n\t-- Dados do Cliente --\n");
        printTCliente(cliente);
    }else
        printf("\n\tCliente inexistente!!!\n");

    return posicao;
}

void consultaClienteCPF(FILE *arq){
    char cpf[12];
    int posicao;
    TCliente cliente;

    printf("\n\tForneça o CPF: ");
    setbuf(stdin, NULL);
    fgets(cpf, 12, stdin);

    retiraEnter(cpf);

    posicao = pesquisaClienteCPF(arq, cpf);
    if(posicao!=-1){
        fseek(arq, posicao*sizeof(TCliente), SEEK_SET);
        fread(&cliente, sizeof(TCliente), 1, arq);

        printf("\n\t-- Dados do Cliente --\n");
        printTCliente(cliente);
    }else
        printf("\n\tCliente inexistente!!!\n");
}

void consultaClienteNome(FILE *arq){
    char nome[11];
    int achou=0;
    TCliente cliente;

    printf("\n\tForneça o prefixo(max 10 caracteres): ");
    setbuf(stdin, NULL);
    fgets(nome, 11, stdin);

    retiraEnter(nome);
    padronizaNome(nome);

    fseek(arq, 0, SEEK_SET);
    while(fread(&cliente, sizeof(TCliente), 1, arq)==1){
        if(strncmp(nome,cliente.nome,strlen(nome))==0){ /*Comprara o prefixo com o nome*/
            if(!achou)
            printf("\n\t-- Dados dos Clientes --\n");

            printTCliente(cliente);
            achou = 1;
        }
    }

    if(!achou)
        printf("\n\tCliente inexistente!!!\n");
}


/*=======================LISTAGEM=======================*/
void listagemClientes(FILE *arq){
    int qtde=0;
    TCliente cliente;

    printf("\n--------------------------------------------------\n");
    printf("---------------- Listagem Cliente ----------------");
    printf("\n--------------------------------------------------\n");

    fseek(arq, 0, SEEK_END);
    if(ftell(arq) > 0){
        fseek(arq, 0, SEEK_SET);
        while(fread(&cliente, sizeof(TCliente), 1, arq)==1) /*Printa os dados recebidos enquanto fread retornar 1*/
            if(cliente.id != 0){
                printTCliente(cliente);
                printf("\t-----------------------------------------");
                qtde=1;
            }

        if(!qtde)
            printf("\n\tNenhum cliente cadastrado!!\n");
    }else
        printf("\n\tNenhum cliente cadastrado!!\n");
}


/*==================PESQUISAS E OUTROS==================*/
int pesquisaClienteID(FILE *arq, unsigned long id){
    int posicao = 0;
    TCliente c;

    fseek(arq, 0, SEEK_SET);

    while(fread(&c, sizeof(TCliente), 1, arq)==1){
        if(c.id != 0){
            if(c.id==id)
                return posicao;
            else
                posicao++;
        }
    }

    return -1;
}

int pesquisaClienteCPF(FILE *arq, char *cpf){
    int posicao = 0;
    TCliente c;

    fseek(arq, 0, SEEK_SET);
    while(fread(&c, sizeof(TCliente), 1, arq)==1){
        if(strcmp(cpf, c.cpf)==0)
            return posicao;
        else
            posicao++;
    }

    return -1;
}

void printTCliente(TCliente cliente){
    printf("\n\tID       = %lu", cliente.id);
    printf("\n\tNome     = %s", cliente.nome);
    printf("\n\tCPF      = %s", cliente.cpf);
    printf("\n\tEmail    = %s", cliente.email);
    printf("\n\tTelefone = %s\n", cliente.telefone);
}

unsigned long getIDCliente(FILE *arq, int posicao){
    TCliente cliente;

    fseek(arq, posicao*sizeof(TCliente), SEEK_SET);
    fread(&cliente, sizeof(TCliente), 1, arq);

    return cliente.id;
}

void getNomeCliente(unsigned long id, char *nome){
    int posicao;
    TCliente cliente;

    FILE *arq;
    abrirArquivo(&arq,"cliente.dat");

    posicao = pesquisaClienteID(arq, id);
    if(posicao!=-1){
        fseek(arq, sizeof(TCliente)*posicao, SEEK_SET);
        fread(&cliente, sizeof(TCliente), 1, arq);

        strcpy(nome, cliente.nome);
    }

    fclose(arq);
}


