#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct{
    unsigned long id;
    char nome[100], cpf[12], email[50], telefone[15];
}TCliente;

/*
Abre/cria um arquivo 'cliente.dat', mostra o menu de manutenção dos clientes e, com a entrada da opção, chama a função checkOpcaoCliente.
        Printa na tela uma mensagem de erro caso não consiga abrir o arquivo.
*/
void areaCliente();

/*
    Permite que o usuário cadastre um novo cliente, validando cada entrada. Ao final, armazena os dados no arquivo 'cliente.dat'.
        Novos IDs: os IDs dos clientes são predefinidos pela função novoIdCliente(), são todos inteiros, positivos, consecutivos e diferentes de zero.
        Obs.: O ID zero (0) indica que o cliente foi excluído e a posiçao é vaga.
*/
void cadastroCliente(FILE *);

/*
    Gera e retorna um ID para o cadastro de um novo cliente. Como a função funciona:
        - verifica quantos clientes já estão cadastrados e retorna como novo ID a quantidade de clientes + 1, gerando assim o ID para o novo cliente.
        - a cada loop a função verifica se o ID corrente é igual a 0 (indica que o cliente foi excluído), caso seja, retorna a quantidade de clientes verificados até o momento + 1.

        Parâmetros: ponteiro FILE que recebe o endereco de memória do arquivo 'cliente.dat'.
        retornos: o ID novo ou reutilizado.
*/
unsigned long novoIdCliente(FILE *);

/*
    Mostra o menu de Alteração, ele possui as opções de alterar e excluir. A função simplesmente verifica se há clientes cadastrados,
    permite a escolha de uma das opções, faz a validação e chama a função correspondente.
        Parâmetros: ponteiro FILE que recebe o endereco de memória do arquivo 'cliente.dat'.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void menuAlterarCliente(FILE *);

/*
    Permite a alteração de alguns dados do cliente. Chama a função que consulta o ID (entrada),
    printa os dados antigos do cliente e permite a sua alteração (caso o cliente exista).
*/
void alterarCliente(FILE *);

/*
    Permite a exclusão do cliente. Chama a função que consulta o ID (entrada),
    printa os dados do cliente e permite a sua exclusão (caso o cliente exista).
        Exclusão: atribuir 0 ao campo do ID.
*/
void excluirCliente(FILE *);

/*
    Mostra o menu de Consulta com todas as suas opções. Verifica se há clientes cadastrados, permite a escolha de uma das opções,
    faz a validação e chama a função correspondente.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void menuConsultaCliente(FILE *);

/*
    Realiza uma consulta de cliente por meio de um ID (entrada). Chama a função pesquisaClienteID para verificar se o ID é valido,
    relaiza uma leitura no arquivo 'cliente.dat'(utilizando a posição recebida pela função chamada anteriormente) armazenando na struct cliente
    e imprime os dados do cliente, caso exista.
        Pode printar uma mensagem de erro caso o cliente não exista.
*/
int consultaClienteID(FILE *);

/*
    Realiza uma consulta de cliente por meio de um CPF(entrada). Chama a função pesquisaClienteCPF para verificar se o CPF é valido,
    relaiza uma leitura no arquivo 'cliente.dat'(utilizando a posição recebida pela função chamada anteriormente) armazenando na struct cliente
    e imprime os dados do cliente, caso exista.
        Pode printar uma mensagem de erro caso o cliente não exista.
*/
void consultaClienteCPF(FILE *);

/*
   Realiza uma consulta de cliente por meio de um Prefixo(entrada). Compara o Prefixo com o nome de todos os clientes, sempre imprimindo os dados dos
   clientes cuja comparação retorne 0.
        Pode printar uma mensagem de erro caso nenhuma comparação retorne 0.
*/
void consultaClienteNome(FILE *);

/*
    Imprime os dados de todos os clientes cadastrados. Verifica se há clientes cadastrados, posiciona o indicador de posição no começo do arquivo 'cliente.dat'
    e percorre todo o arquivo, imprimindo os dados com a função printTCliente.
*/
void listagemClientes(FILE *);

/*
    Verifica se o cliente com o ID recebido por parâmetro existe. Retorna a sua posição caso exista ou -1 caso não.
        Parâmetros: unsigned long para o ID, ponteiro FILE para o arquivo 'cliente.dat'.
        Retorno: posição dos dados do cliente ou -1 (inexistente).
*/
int pesquisaClienteID(FILE *, unsigned long);

/*
    Verifica se o cliente com o CPF recebido por parâmetro existe. Retorna a sua posição caso exista ou -1 caso não.
        Parâmetros: char[] para o CPF, ponteiro FILE para o arquivo 'cliente.dat'.
        Retorno: posição dos dados do cliente ou -1 (inexistente).
*/
int pesquisaClienteCPF(FILE *, char *);

/*
    Printa na tela todos os dados da Struct recebida por parâmetro.
*/
void printTCliente(TCliente);

/*
Recebe uma posição (arquivo "cliente.dat") e retorna o id do cliente armazenado na mesma.
*/
unsigned long getIDCliente(FILE *, int);

/*
Recebe um id e armazena na variável char * o nome do cliente correspondente.
*/
void getNomeCliente(unsigned long, char *);

#endif /*CLIENTE_H_INCLUDED*/
