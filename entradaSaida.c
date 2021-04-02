#include <stdio.h>
#include "entradaSaida.h"
#include "funcGerais.h"

void printLogo(){
    printf("\n--------------------------------------------------\n");
    printf("--- LOUCO DAS PEDRAS - PRODUTOS FARMACOLÓGICOS ---");
    printf("\n--------------------------------------------------\n");
}

void printMenuOption(){
    printf("\n\t1 - Manutenção Cliente\n\t2 - Manutenção Vendedor\n\t3 - Manutenção Fornecedor\n\t4 - Cadastro de Produtos\n\t5 - Efetuar Venda\n\t6 - Efetuar Compra\n\t7 - Atualizar Preço\n\t8 - Relátorios\n\t9 - Sair\n");
}

void printInvOption(char *str){
    printf("\n---- %s inválida!! Tente novamente. ----\n", str);
}

void escolhaSimNao(int *op){
    do{
        printf("\n\t1 - Sim\n\t2 - Não");
        printf("\n\tEscolha uma opção: ");
        scanf("%d", op);

        if(*op!=1 && *op!=2)
            printInvOption("Opção");
    }while(*op!=1 && *op!=2);
}

void entradaNome(char *nome){
    int valido;
    do{
        printf("\n\tNome: ");
        setbuf(stdin, NULL);
        fgets(nome, 100, stdin);

        valido = retiraEnter(nome);

        if(valido)
            printf("\n\tO nome fornecido está vazio!! Tente Novamente!\n");
        else
            padronizaNome(nome);

    }while(valido);
}

void entradaCPF(char *cpf){
    int valido;
    do{
        printf("\tCPF (somente os números): ");
        setbuf(stdin, NULL);
        fgets(cpf, 12, stdin);

        valido = retiraEnter(cpf);
        valido = validaCPF(cpf);

        if(valido)
            printInvOption("CPF");

    }while(valido);
}

void entradaCNPJ(char *cnpj){
    int valido;
    do{
        printf("\tCNPJ (somente os números): ");
        setbuf(stdin, NULL);
        fgets(cnpj, 15, stdin);

        valido = retiraEnter(cnpj);
        valido = validaCNPJ(cnpj);

        if(valido)
            printInvOption("CNPJ");

        setbuf(stdin, NULL);
    }while(valido);
}

void entradaEmail(char *email){
    int valido;
    do{
        printf("\tEmail: ");
        setbuf(stdin, NULL);
        fgets(email, 50, stdin);

        valido = retiraEnter(email);

        if(valido)
            printf("\n\tO email é um campo obrigatório!! Tente Novamente!\n");
        else
            padronizaNome(email);

    }while(valido);
}

void entradaTelefone(char *tel){
    int valido, vazio;
    do{
        printf("\tTelefone: ");
        setbuf(stdin, NULL);
        fgets(tel, 15, stdin);

        vazio = retiraEnter(tel);
        valido = validaTelefone(tel);

        if(vazio)
            printf("\n\tO número de telefone é um campo obrigatório!! Tente Novamente!\n");
        else if(valido)
            printf("\n\tO número de telefone deve possuir apenas caracteres numéricos!! Tente Novamente!\n");
    }while(vazio || valido);
}

void entradaSenha(char *senha){
    int valido;
    do{
        printf("\tSenha: ");
        setbuf(stdin, NULL);
        fgets(senha, 20, stdin);

        valido = retiraEnter(senha);

        if(valido)
            printf("\n\tA senha é um campo obrigatório!! Tente Novamente!\n");
        else
            padronizaNome(senha);
    }while(valido);
}

void entradaPrecoUnit(float *preco){
    int valido;
    do{
        printf("\tPreço Unitário: R$");
        scanf("%f", preco);

        valido=0;
        if(*preco<0){
            printInvOption("Preço  Unitário");
            valido = 1;
        }

    }while(valido);
}

void entradaData(char *data){
    int valido;
    do{
        printf("\n\tObedeça o formato DD/MM/AAAA\n\tForneça a Data: ");
        setbuf(stdin, NULL);
        fgets(data, 11, stdin);

        valido = retiraEnter(data);
        valido = validaData(data);

        if(valido)
            printf("\n\tData inválida!! Tente Novamente!\n");

    }while(valido);
}





