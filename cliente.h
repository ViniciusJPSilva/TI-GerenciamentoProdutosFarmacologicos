#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct{
    unsigned long id;
    char nome[100], cpf[12], email[50], telefone[15];
}TCliente;

/*
Abre/cria um arquivo 'cliente.dat', mostra o menu de manuten��o dos clientes e, com a entrada da op��o, chama a fun��o checkOpcaoCliente.
        Printa na tela uma mensagem de erro caso n�o consiga abrir o arquivo.
*/
void areaCliente();

/*
    Permite que o usu�rio cadastre um novo cliente, validando cada entrada. Ao final, armazena os dados no arquivo 'cliente.dat'.
        Novos IDs: os IDs dos clientes s�o predefinidos pela fun��o novoIdCliente(), s�o todos inteiros, positivos, consecutivos e diferentes de zero.
        Obs.: O ID zero (0) indica que o cliente foi exclu�do e a posi�ao � vaga.
*/
void cadastroCliente(FILE *);

/*
    Gera e retorna um ID para o cadastro de um novo cliente. Como a fun��o funciona:
        - verifica quantos clientes j� est�o cadastrados e retorna como novo ID a quantidade de clientes + 1, gerando assim o ID para o novo cliente.
        - a cada loop a fun��o verifica se o ID corrente � igual a 0 (indica que o cliente foi exclu�do), caso seja, retorna a quantidade de clientes verificados at� o momento + 1.

        Par�metros: ponteiro FILE que recebe o endereco de mem�ria do arquivo 'cliente.dat'.
        retornos: o ID novo ou reutilizado.
*/
unsigned long novoIdCliente(FILE *);

/*
    Mostra o menu de Altera��o, ele possui as op��es de alterar e excluir. A fun��o simplesmente verifica se h� clientes cadastrados,
    permite a escolha de uma das op��es, faz a valida��o e chama a fun��o correspondente.
        Par�metros: ponteiro FILE que recebe o endereco de mem�ria do arquivo 'cliente.dat'.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void menuAlterarCliente(FILE *);

/*
    Permite a altera��o de alguns dados do cliente. Chama a fun��o que consulta o ID (entrada),
    printa os dados antigos do cliente e permite a sua altera��o (caso o cliente exista).
*/
void alterarCliente(FILE *);

/*
    Permite a exclus�o do cliente. Chama a fun��o que consulta o ID (entrada),
    printa os dados do cliente e permite a sua exclus�o (caso o cliente exista).
        Exclus�o: atribuir 0 ao campo do ID.
*/
void excluirCliente(FILE *);

/*
    Mostra o menu de Consulta com todas as suas op��es. Verifica se h� clientes cadastrados, permite a escolha de uma das op��es,
    faz a valida��o e chama a fun��o correspondente.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void menuConsultaCliente(FILE *);

/*
    Realiza uma consulta de cliente por meio de um ID (entrada). Chama a fun��o pesquisaClienteID para verificar se o ID � valido,
    relaiza uma leitura no arquivo 'cliente.dat'(utilizando a posi��o recebida pela fun��o chamada anteriormente) armazenando na struct cliente
    e imprime os dados do cliente, caso exista.
        Pode printar uma mensagem de erro caso o cliente n�o exista.
*/
int consultaClienteID(FILE *);

/*
    Realiza uma consulta de cliente por meio de um CPF(entrada). Chama a fun��o pesquisaClienteCPF para verificar se o CPF � valido,
    relaiza uma leitura no arquivo 'cliente.dat'(utilizando a posi��o recebida pela fun��o chamada anteriormente) armazenando na struct cliente
    e imprime os dados do cliente, caso exista.
        Pode printar uma mensagem de erro caso o cliente n�o exista.
*/
void consultaClienteCPF(FILE *);

/*
   Realiza uma consulta de cliente por meio de um Prefixo(entrada). Compara o Prefixo com o nome de todos os clientes, sempre imprimindo os dados dos
   clientes cuja compara��o retorne 0.
        Pode printar uma mensagem de erro caso nenhuma compara��o retorne 0.
*/
void consultaClienteNome(FILE *);

/*
    Imprime os dados de todos os clientes cadastrados. Verifica se h� clientes cadastrados, posiciona o indicador de posi��o no come�o do arquivo 'cliente.dat'
    e percorre todo o arquivo, imprimindo os dados com a fun��o printTCliente.
*/
void listagemClientes(FILE *);

/*
    Verifica se o cliente com o ID recebido por par�metro existe. Retorna a sua posi��o caso exista ou -1 caso n�o.
        Par�metros: unsigned long para o ID, ponteiro FILE para o arquivo 'cliente.dat'.
        Retorno: posi��o dos dados do cliente ou -1 (inexistente).
*/
int pesquisaClienteID(FILE *, unsigned long);

/*
    Verifica se o cliente com o CPF recebido por par�metro existe. Retorna a sua posi��o caso exista ou -1 caso n�o.
        Par�metros: char[] para o CPF, ponteiro FILE para o arquivo 'cliente.dat'.
        Retorno: posi��o dos dados do cliente ou -1 (inexistente).
*/
int pesquisaClienteCPF(FILE *, char *);

/*
    Printa na tela todos os dados da Struct recebida por par�metro.
*/
void printTCliente(TCliente);

/*
Recebe uma posi��o (arquivo "cliente.dat") e retorna o id do cliente armazenado na mesma.
*/
unsigned long getIDCliente(FILE *, int);

/*
Recebe um id e armazena na vari�vel char * o nome do cliente correspondente.
*/
void getNomeCliente(unsigned long, char *);

#endif /*CLIENTE_H_INCLUDED*/
