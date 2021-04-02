#ifndef VENDEDOR_H_INCLUDED
#define VENDEDOR_H_INCLUDED

typedef struct{
    unsigned long id;
    char nome[100], cpf[12], email[50], telefone[15], password[20];
}TVendedor;

/*
    Abre/cria um arquivo 'vendedor.dat', mostra o menu de manuten��o dos vendedores e, com a entrada da op��o, chama a fun��o checkOpcaoVend.
        Printa na tela uma mensagem de erro caso n�o consiga abrir o arquivo.
*/
void areaVendedor();

/*
    Permite que o usu�rio cadastre um novo vendedor, validando cada entrada. Ao final, armazena os dados no arquivo 'vendedor.dat'.
        Novos IDs: os IDs dos vendedores s�o predefinidos pela fun��o novoIdVend(), s�o todos inteiros, positivos, consecutivos e diferentes de zero.
        Obs.: O ID zero (0) indica que o vendedor foi exclu�do e a posi�ao � vaga.
*/
void cadastroVend(FILE *);

/*
    Gera e retorna um ID para o cadastro de um novo vendedor. Como a fun��o funciona:
        - verifica quantos vendedores j� est�o cadastrados e retorna como novo ID a quantidade de vendedores + 1, gerando assim o ID para o novo vendedor.
        - a cada loop a fun��o verifica se o ID corrente � igual a 0 (indica que o vendedor foi exclu�do), caso seja, retorna a quantidade de vendedores verificados at� o momento + 1.

        Par�metros: ponteiro FILE que recebe o endereco de mem�ria do arquivo 'vendedor.dat'.
        retornos: o ID novo ou reutilizado.
*/
unsigned long novoIdVend(FILE *);

/*
    Mostra o menu de Altera��o, ele possui as op��es de alterar e excluir. A fun��o simplesmente verifica se h� vendedores cadastrados,
    permite a escolha de uma das op��es, faz a valida��o e chama a fun��o correspondente.
        Par�metros: ponteiro FILE que recebe o endereco de mem�ria do arquivo 'vendedor.dat'.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void menuAlterarVend(FILE *);

/*
    Permite a altera��o de alguns dados do vendedor. Chama a fun��o que consulta o ID (entrada),
    printa os dados antigos do vendedor e permite a sua altera��o (caso o vendedor exista).
*/
void alterarVend(FILE *);

/*
    Permite a exclus�o do vendedor. Chama a fun��o que consulta o ID (entrada),
    printa os dados do vendedor e permite a sua exclus�o (caso o vendedor exista).
        Exclus�o: atribuir 0 ao campo do ID.
*/
void excluirVend(FILE *);

/*
    Mostra o menu de Consulta com todas as suas op��es. Verifica se h� vendedores cadastrados, permite a escolha de uma das op��es,
    faz a valida��o e chama a fun��o correspondente.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void menuConsultaVend(FILE *);

/*
    Realiza uma consulta de vendedor por meio de um ID (entrada). Chama a fun��o pesquisaVendID para verificar se o ID � valido,
    relaiza uma leitura no arquivo 'vendedor.dat'(utilizando a posi��o recebida pela fun��o chamada anteriormente) armazenando na struct vendedor
    e imprime os dados do vendedor, caso exista.
        Pode printar uma mensagem de erro caso o vendedor n�o exista.
*/
int consultaVendID(FILE *);

/*
    Realiza uma consulta de vendedor por meio de um CPF(entrada). Chama a fun��o pesquisaVendCPF para verificar se o CPF � valido,
    realiza uma leitura no arquivo 'vendedor.dat'(utilizando a posi��o recebida pela fun��o chamada anteriormente) armazenando na struct TVendedor
    e imprime os dados do vendedor, caso exista.
        Pode printar uma mensagem de erro caso o vendedor n�o exista.
*/
unsigned long consultaVendCPF(FILE *);

/*
   Realiza uma consulta de vendedor por meio de um Prefixo(entrada). Compara o Prefixo com o nome de todos os vendedores, sempre imprimindo os dados dos
   vendedores cuja compara��o retorne 0.
        Pode printar uma mensagem de erro caso nenhuma compara��o retorne 0.
*/
void consultaVendNome(FILE *);

/*
    Imprime os dados de todos os vendedores cadastrados. Verifica se h� vendedores cadastrados, posiciona o indicador de posi��o no come�o do arquivo 'vendedor.dat'
    e percorre todo o arquivo, imprimindo os dados com a fun��o printTVend.
*/
void listagemVend(FILE *);

/*
    Printa na tela todos os dados da Struct recebida por par�metro.
*/
void printTVend(TVendedor);

/*
    Verifica se o vendedor com o ID recebido por par�metro existe. Retorna a sua posi��o caso exista ou -1 caso n�o.
        Par�metros: unsigned long para o ID, ponteiro FILE para o arquivo 'vendedor.dat'.
        Retorno: posi��o dos dados do vendedor ou -1 (inexistente).
*/
int pesquisaVendID(FILE *, unsigned long);

/*
    Verifica se o vendedor com o CPF recebido por par�metro existe. Retorna a sua posi��o caso exista ou -1 caso n�o.
        Par�metros: char[] para o CPF, ponteiro FILE para o arquivo 'vendedor.dat'.
        Retorno: posi��o dos dados do vendedor ou -1 (inexistente).
*/
int pesquisaVendCPF(FILE *, char *);

/*
    Verifica se o vendedor com o EMAIL recebido por par�metro existe. Retorna a sua posi��o caso exista ou -1 caso n�o.
        Par�metros: char[] para o email, ponteiro FILE para o arquivo 'vendedor.dat'.
        Retorno: posi��o dos dados do vendedor ou -1 (inexistente).
*/
int pesquisaVendEmail(FILE *, char *);

/*
Recebe uma posi��o (arquivo "vendedor.dat") e retorna o id do vendedor armazenado nessa mesma posi��o.
*/
unsigned long getIDVendedor(FILE *, int);

/*
Recebe um id e armazena na vari�vel char * a senha do vendedor correspondente.
*/
void getSenhaVendedor(FILE *, unsigned long , char *);

/*
Recebe um id e armazena na vari�vel char * o nome do vendedor correspondente.
*/
void getNomeVendedor( unsigned long, char *);

#endif /*VENDEDOR_H_INCLUDED*/
