#ifndef ENTRADASAIDA_H_INCLUDED
#define ENTRADASAIDA_H_INCLUDED

/*Impress�o da logo*/
void printLogo();

/*Impress�o das op��es do menu principal*/
void printMenuOption();

/*Printa a string recebida + "op�ao inv�lida!"*/
void printInvOption(char *);

/*Apresenta as op��es de "Sim" e "N�o" pro usu�rio, recebe e valida a entrada do mesmo*/
void escolhaSimNao(int *);

/*Recebe, valida e padroniza um Nome (string) fornecido pelo do usu�rio*/
void entradaNome(char *);

/*Recebe, valida e padroniza um CPF (string) fornecido pelo do usu�rio*/
void entradaCPF(char *);

/*Recebe, valida e padroniza um CNPJ (string) fornecido pelo do usu�rio*/
void entradaCNPJ(char *);

/*Recebe, valida e padroniza um Email (string) fornecido pelo do usu�rio*/
void entradaEmail(char *);

/*Recebe, valida e padroniza um N�mero de Telefone (string) fornecido pelo do usu�rio*/
void entradaTelefone(char *);

/*Recebe, valida e padroniza uma Senha (string) fornecida pelo do usu�rio*/
void entradaSenha(char *);

/*Recebe e valida uma Senha (string) fornecido pelo do usu�rio*/
void entradaPrecoUnit(float *);

/*Recebe e valida uma Data (string) fornecida pelo do usu�rio*/
void entradaData(char *);

#endif /*ENTRADASAIDA_H_INCLUDED*/
