#ifndef ENTRADASAIDA_H_INCLUDED
#define ENTRADASAIDA_H_INCLUDED

/*Impressão da logo*/
void printLogo();

/*Impressão das opções do menu principal*/
void printMenuOption();

/*Printa a string recebida + "opçao inválida!"*/
void printInvOption(char *);

/*Apresenta as opções de "Sim" e "Não" pro usuário, recebe e valida a entrada do mesmo*/
void escolhaSimNao(int *);

/*Recebe, valida e padroniza um Nome (string) fornecido pelo do usuário*/
void entradaNome(char *);

/*Recebe, valida e padroniza um CPF (string) fornecido pelo do usuário*/
void entradaCPF(char *);

/*Recebe, valida e padroniza um CNPJ (string) fornecido pelo do usuário*/
void entradaCNPJ(char *);

/*Recebe, valida e padroniza um Email (string) fornecido pelo do usuário*/
void entradaEmail(char *);

/*Recebe, valida e padroniza um Número de Telefone (string) fornecido pelo do usuário*/
void entradaTelefone(char *);

/*Recebe, valida e padroniza uma Senha (string) fornecida pelo do usuário*/
void entradaSenha(char *);

/*Recebe e valida uma Senha (string) fornecido pelo do usuário*/
void entradaPrecoUnit(float *);

/*Recebe e valida uma Data (string) fornecida pelo do usuário*/
void entradaData(char *);

#endif /*ENTRADASAIDA_H_INCLUDED*/
