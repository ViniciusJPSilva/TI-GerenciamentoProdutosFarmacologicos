#include <stdio.h>
#include "entradaSaida.h"
#include "funcGerais.h"

void printLogo(){
    printf("\n--------------------------------------------------\n");
    printf("--- LOUCO DAS PEDRAS - PRODUTOS FARMACOL�GICOS ---");
    printf("\n--------------------------------------------------\n");
}

void printMenuOption(){
    printf("\n\t1 - Manuten��o Cliente\n\t2 - Manuten��o Vendedor\n\t3 - Manuten��o Fornecedor\n\t4 - Cadastro de Produtos\n\t5 - Efetuar Venda\n\t6 - Efetuar Compra\n\t7 - Atualizar Pre�o\n\t8 - Rel�torios\n\t9 - Sair\n");
}

void printInvOption(char *str){
    printf("\n---- %s inv�lida!! Tente novamente. ----\n", str);
}

void escolhaSimNao(int *op){
    do{
        printf("\n\t1 - Sim\n\t2 - N�o");
        printf("\n\tEscolha uma op��o: ");
        scanf("%d", op);

        if(*op!=1 && *op!=2)
            printInvOption("Op��o");
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
            printf("\n\tO nome fornecido est� vazio!! Tente Novamente!\n");
        else
            padronizaNome(nome);

    }while(valido);
}

void entradaCPF(char *cpf){
    int valido;
    do{
        printf("\tCPF (somente os n�meros): ");
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
        printf("\tCNPJ (somente os n�meros): ");
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
            printf("\n\tO email � um campo obrigat�rio!! Tente Novamente!\n");
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
            printf("\n\tO n�mero de telefone � um campo obrigat�rio!! Tente Novamente!\n");
        else if(valido)
            printf("\n\tO n�mero de telefone deve possuir apenas caracteres num�ricos!! Tente Novamente!\n");
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
            printf("\n\tA senha � um campo obrigat�rio!! Tente Novamente!\n");
        else
            padronizaNome(senha);
    }while(valido);
}

void entradaPrecoUnit(float *preco){
    int valido;
    do{
        printf("\tPre�o Unit�rio: R$");
        scanf("%f", preco);

        valido=0;
        if(*preco<0){
            printInvOption("Pre�o  Unit�rio");
            valido = 1;
        }

    }while(valido);
}

void entradaData(char *data){
    int valido;
    do{
        printf("\n\tObede�a o formato DD/MM/AAAA\n\tForne�a a Data: ");
        setbuf(stdin, NULL);
        fgets(data, 11, stdin);

        valido = retiraEnter(data);
        valido = validaData(data);

        if(valido)
            printf("\n\tData inv�lida!! Tente Novamente!\n");

    }while(valido);
}





