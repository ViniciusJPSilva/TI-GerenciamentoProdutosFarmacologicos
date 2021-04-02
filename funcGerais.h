#ifndef FUNCGERAIS_H_INCLUDED
#define FUNCGERAIS_H_INCLUDED

/*
Tenta abrir um arquivo, retorna o endereço do arquivo caso consiga ou NULL caso não consiga*/
void abrirArquivo(FILE **, char *);

/*
Realiza uma verificação na string e retira o caracter '\n' caso ele exista*/
int retiraEnter(char *);

/*
Função responsável por padronizar a string recebida.
    1° - Verifica se há caracteres acentuados e tenta retirar os acentos dos mesmos
    2° - Verifica se há caracteres em CaixaBaixa e tenta converte-los para CaixaAlta*/
void padronizaNome(char *);

/*
Compara o caracter recebido com uma lista de caracteres acentuados, caso a comparação retorne 'true' o acento é retirado e a função o retorna*/
char retiraAcento(char);

/*
Validação do CPF baseado na soma de seus números
    retorna 0 caso seja válido
    retorna 1 caso seja inválido
*/
int validaCPF(char *);

/*
Validação do CNPJ baseado no sistema de digitos verificadores
    retorna 0 caso seja válido
    retorna 1 caso seja inválido
*/
int validaCNPJ(char *);

/*
Preenche a string recebida com a data atual do sistema. Formato: "DD/MM/AAAA\0"*/
void geraData(char *);

/*
Validação do Telefone. Verifica se há algum outro caracter além dos numéricos
    retorna 0 caso seja válido (Encontrou somente números)
    retorna 1 caso seja inválido (Encontrou outro tipo de caracter)
*/
int validaTelefone(char *);

/*
Validação da string data. Verifica se o formato obedece o padrão DD/MM/AAAA e valida o dia, o mês e o ano
    retorna 0 caso seja válido
    retorna 1 caso seja inválido
*/
int validaData(char *);

/*
Verifica se a data passada pelo parâmetro 1 é menor que a data passada pelo parâmetro 2.
    retorna 1 caso seja.
    retorna 0 caso não seja.
*/
int verificaDataMenor(char *, char *);

#endif /*FUNCGERAIS_H_INCLUDED*/
