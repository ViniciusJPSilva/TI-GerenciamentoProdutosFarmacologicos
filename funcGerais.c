#include <string.h>
#include <stdio.h>
#include <time.h>
#include "funcGerais.h"

void abrirArquivo(FILE **arq, char *nome){
    *arq = fopen(nome, "rb+");
    if(*arq==NULL)
        *arq = fopen(nome, "wb+");
}

int retiraEnter(char *str){
    if(str[0]!='\n'){
        if(str[strlen(str)-1]=='\n')
            str[strlen(str)-1] = '\0';
    }else
        return 1;

    return 0;
}

void padronizaNome(char *nome){
    /*Como alguns produtos podem conter numerais em seus nomes a função não realiza a retirada dos mesmos*/
    int i;
    for(i=0; i<strlen(nome); i++){
        /*Verificando se o caracter é especial e tentando retirar sua acentuação*/
        if((nome[i]<65 || nome[i]>90) && (nome[i]<97 || nome[i]>122))
            nome[i] = retiraAcento(nome[i]);

        /*Transformando o caracter de caixa baixa para caixa alta*/
        if(nome[i]>=97 && nome[i]<=122)
            nome[i] -= 32;
    }
}

char retiraAcento(char c){
    int i;
    /*ÄÅÁÂÀÃäáâàãÉÊËÈéêëèÍÎÏÌíîïìÖÓÔÒÕöóôòõÜÚÛüúûùÇç*/
    int comAcento [] = {142,143,181,182,183,199,132,160,131,133,198,144,210,211,212,130,136,137,138,214,215,216,222,161,140,139,141,153,224,226,227,229,148,162,147,149,228,154,233,234,129,163,150,151,128,135};
    /*AAAAAAaaaaaEEEEeeeeIIIIiiiiOOOOOoooooUUUuuuuCc*/
    int semAcento [] = {65,65,65,65,65,65,97,97,97,97,97,69,69,69,69,101,101,101,101,73,73,73,73,105,105,105,105,79,79,79,79,79,111,111,111,111,111,85,85,85,117,117,117,117,67,99};

    /*Compara o char acentuado com cada codigo ASCII do vetor 'comAcento' e retorna o seu equivalente sem acento
        Alguns caracteres estavam com código < 0, somando 256 alcancei seu respectivo código positivo*/
    for(i=0; i<47; i++)
        if(c+256 == comAcento[i])
            return semAcento[i];

    return c;
}

int validaCPF(char *cpf){
    int i, soma=0;
    if(strlen(cpf)==11){
        /*Converte cada caracter do vetor cpf para seu inteiro equivalente*/
        for (i=0; cpf[i]!='\0'; i++)
            soma = soma + (cpf[i]-48);

        switch (soma){
            case 10:
            case 11:
            case 12:
            case 21:
            case 22:
            case 23:
            case 32:
            case 33:
            case 34:
            case 43:
            case 44:
            case 45:
            case 54:
            case 55:
            case 56:
            case 65:
            case 66:
            case 67:
            case 76:
            case 77:
            case 78:
            case 87:
            case 88:
                return 0;
                break;
            default:
                return 1;
        }
    }else
        return 1;
}

int validaCNPJ(char *cnpjChar){
    int i, soma=0;
    int cnpj[14], base[] = {6,5,4,3,2,9,8,7,6,5,4,3,2}, res[12];

    if(strlen(cnpjChar)==14){
        /*Converte cada caracter do vetor cnpj para seu inteiro equivalente*/
        for (i=0; cnpjChar[i]!='\0'; i++){
            cnpj[i] = (cnpjChar[i]-48);
        }

        /*Validando o primeiro digito verificador*/
        for(i=0; i<12; i++){
            res[i] = cnpj[i] * base[i+1];
            soma += res[i];
        }

        soma %= 11;
        if(soma < 2)
             soma = 0;
        else
            soma = 11 - soma;

        if(cnpj[12]==soma){
            /*Validando o segundo digito verificador*/
            soma = 0;
            for(i=0; i<13; i++){
                res[i] = cnpj[i] * base[i];
                soma += res[i];
            }

            soma %= 11;
            if(soma < 2)
                 soma = 0;
            else
                soma = 11 - soma;

            if(cnpj[13]==soma)
                return 0;
        }
    }

    return 1;
}

int validaTelefone(char *tel){
    int i;
    for(i=0; i<strlen(tel); i++)
        if(tel[i]<48 || tel[i]>57)
            return 1;

    return 0;
}

void geraData(char *data){
    /*Armazenando a data atual do sistema em uma string*/
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    sprintf(data,"%.2d/%.2d/%.4d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    data[10] = '\0';
}

int validaData(char *data){
    int i, dia, mes, ano;
    /*Verificando se a string possui apenas números e barras*/
    for(i=0; i<strlen(data);i++)
        if(i!=2 && i!=5){
            if(data[i]<48 || data[i]>57)
                return 1;
        }else if(data[i]!=47)
            return 1;
    /*Transformando de string/char para int*/
    dia = (data[0]-48)*10 + (data[1]-48);
    mes = (data[3]-48)*10 + (data[4]-48);
    ano = (data[6]-48)*1000 + (data[7]-48)*100 + (data[8]-48)*10 + (data[9]-48);

    /*Validando o dia, o mês e o ano*/
    if(ano>=0){
        switch(mes){
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if(dia<1 || dia>31)
                    return 1;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if(dia<1 || dia>30)
                    return 1;
                break;
            case 2:
                if((ano%4==0) && ((ano%100!=0) || (ano%400==0))){ /*Verifica se o ano é bissexto*/
                    if(dia<01 || dia>29){
                        return 1;
                    }
                }else
                    if(dia<01 || dia>28)
                        return 1;
                break;
            default:
                return 1;
        }
    }else
        return 1;

    return 0;
}

int verificaDataMenor(char *dataMenor, char *dataMaior){
    int dia1, dia2, mes1, mes2, ano1, ano2;

    /*Transformando as datas char para int*/
    dia1 = (dataMenor[0]-48)*10 + dataMenor[1]-48;
    dia2 = (dataMaior[0]-48)*10 + dataMaior[1]-48;
    mes1 = (dataMenor[3]-48)*10 + dataMenor[4]-48;
    mes2 = (dataMaior[3]-48)*10 + dataMaior[4]-48;
    ano1 = (dataMenor[6]-48)*1000 + (dataMenor[7]-48)*100 + (dataMenor[8]-48)*10 + dataMenor[9]-48;
    ano2 = (dataMaior[6]-48)*1000 + (dataMaior[7]-48)*100 + (dataMaior[8]-48)*10 + dataMaior[9]-48;

    if (ano1 < ano2) /*compara os anos*/
        return 1;
    if (ano1 == ano2 && mes1 < mes2) /*compara os meses -  tendo certeza que o ano de d1 é igual ao ano de d2*/
        return 1;
    if (ano1 == ano2 && mes1 == mes2 && dia1 < dia2) /*compara os dias -  tendo certeza que o ano e o mês de d1 e d2 são iguais*/
        return 1;
    return 0;

}

