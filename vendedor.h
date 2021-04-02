#ifndef VENDEDOR_H_INCLUDED
#define VENDEDOR_H_INCLUDED

typedef struct{
    unsigned long id;
    char nome[100], cpf[12], email[50], telefone[15], password[20];
}TVendedor;

/*
    Abre/cria um arquivo 'vendedor.dat', mostra o menu de manutenção dos vendedores e, com a entrada da opção, chama a função checkOpcaoVend.
        Printa na tela uma mensagem de erro caso não consiga abrir o arquivo.
*/
void areaVendedor();

/*
    Permite que o usuário cadastre um novo vendedor, validando cada entrada. Ao final, armazena os dados no arquivo 'vendedor.dat'.
        Novos IDs: os IDs dos vendedores são predefinidos pela função novoIdVend(), são todos inteiros, positivos, consecutivos e diferentes de zero.
        Obs.: O ID zero (0) indica que o vendedor foi excluído e a posiçao é vaga.
*/
void cadastroVend(FILE *);

/*
    Gera e retorna um ID para o cadastro de um novo vendedor. Como a função funciona:
        - verifica quantos vendedores já estão cadastrados e retorna como novo ID a quantidade de vendedores + 1, gerando assim o ID para o novo vendedor.
        - a cada loop a função verifica se o ID corrente é igual a 0 (indica que o vendedor foi excluído), caso seja, retorna a quantidade de vendedores verificados até o momento + 1.

        Parâmetros: ponteiro FILE que recebe o endereco de memória do arquivo 'vendedor.dat'.
        retornos: o ID novo ou reutilizado.
*/
unsigned long novoIdVend(FILE *);

/*
    Mostra o menu de Alteração, ele possui as opções de alterar e excluir. A função simplesmente verifica se há vendedores cadastrados,
    permite a escolha de uma das opções, faz a validação e chama a função correspondente.
        Parâmetros: ponteiro FILE que recebe o endereco de memória do arquivo 'vendedor.dat'.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void menuAlterarVend(FILE *);

/*
    Permite a alteração de alguns dados do vendedor. Chama a função que consulta o ID (entrada),
    printa os dados antigos do vendedor e permite a sua alteração (caso o vendedor exista).
*/
void alterarVend(FILE *);

/*
    Permite a exclusão do vendedor. Chama a função que consulta o ID (entrada),
    printa os dados do vendedor e permite a sua exclusão (caso o vendedor exista).
        Exclusão: atribuir 0 ao campo do ID.
*/
void excluirVend(FILE *);

/*
    Mostra o menu de Consulta com todas as suas opções. Verifica se há vendedores cadastrados, permite a escolha de uma das opções,
    faz a validação e chama a função correspondente.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void menuConsultaVend(FILE *);

/*
    Realiza uma consulta de vendedor por meio de um ID (entrada). Chama a função pesquisaVendID para verificar se o ID é valido,
    relaiza uma leitura no arquivo 'vendedor.dat'(utilizando a posição recebida pela função chamada anteriormente) armazenando na struct vendedor
    e imprime os dados do vendedor, caso exista.
        Pode printar uma mensagem de erro caso o vendedor não exista.
*/
int consultaVendID(FILE *);

/*
    Realiza uma consulta de vendedor por meio de um CPF(entrada). Chama a função pesquisaVendCPF para verificar se o CPF é valido,
    realiza uma leitura no arquivo 'vendedor.dat'(utilizando a posição recebida pela função chamada anteriormente) armazenando na struct TVendedor
    e imprime os dados do vendedor, caso exista.
        Pode printar uma mensagem de erro caso o vendedor não exista.
*/
unsigned long consultaVendCPF(FILE *);

/*
   Realiza uma consulta de vendedor por meio de um Prefixo(entrada). Compara o Prefixo com o nome de todos os vendedores, sempre imprimindo os dados dos
   vendedores cuja comparação retorne 0.
        Pode printar uma mensagem de erro caso nenhuma comparação retorne 0.
*/
void consultaVendNome(FILE *);

/*
    Imprime os dados de todos os vendedores cadastrados. Verifica se há vendedores cadastrados, posiciona o indicador de posição no começo do arquivo 'vendedor.dat'
    e percorre todo o arquivo, imprimindo os dados com a função printTVend.
*/
void listagemVend(FILE *);

/*
    Printa na tela todos os dados da Struct recebida por parâmetro.
*/
void printTVend(TVendedor);

/*
    Verifica se o vendedor com o ID recebido por parâmetro existe. Retorna a sua posição caso exista ou -1 caso não.
        Parâmetros: unsigned long para o ID, ponteiro FILE para o arquivo 'vendedor.dat'.
        Retorno: posição dos dados do vendedor ou -1 (inexistente).
*/
int pesquisaVendID(FILE *, unsigned long);

/*
    Verifica se o vendedor com o CPF recebido por parâmetro existe. Retorna a sua posição caso exista ou -1 caso não.
        Parâmetros: char[] para o CPF, ponteiro FILE para o arquivo 'vendedor.dat'.
        Retorno: posição dos dados do vendedor ou -1 (inexistente).
*/
int pesquisaVendCPF(FILE *, char *);

/*
    Verifica se o vendedor com o EMAIL recebido por parâmetro existe. Retorna a sua posição caso exista ou -1 caso não.
        Parâmetros: char[] para o email, ponteiro FILE para o arquivo 'vendedor.dat'.
        Retorno: posição dos dados do vendedor ou -1 (inexistente).
*/
int pesquisaVendEmail(FILE *, char *);

/*
Recebe uma posição (arquivo "vendedor.dat") e retorna o id do vendedor armazenado nessa mesma posição.
*/
unsigned long getIDVendedor(FILE *, int);

/*
Recebe um id e armazena na variável char * a senha do vendedor correspondente.
*/
void getSenhaVendedor(FILE *, unsigned long , char *);

/*
Recebe um id e armazena na variável char * o nome do vendedor correspondente.
*/
void getNomeVendedor( unsigned long, char *);

#endif /*VENDEDOR_H_INCLUDED*/
