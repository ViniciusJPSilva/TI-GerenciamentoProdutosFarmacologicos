#ifndef FORNECEDOR_H_INCLUDED
#define FORNECEDOR_H_INCLUDED

typedef struct{
    unsigned long id;
    char nome[100], cnpj[15], email[50], telefone[15];
}TFornecedor;

/*
    Abre/cria um arquivo 'fornecedor.dat', mostra o menu de manuten��o dos fornecedores e, com a entrada da op��o, chama a fun��o checkOpcaoFornc.
        Printa na tela uma mensagem de erro caso n�o consiga abrir o arquivo.
*/
void areaFornecedor();

/*
    Permite que o usu�rio cadastre um novo fornecedor, validando cada entrada. Ao final, armazena os dados no arquivo 'fornecedor.dat'.
        Novos IDs: os IDs dos fornecedores s�o predefinidos pela fun��o novoIdFornc(), s�o todos inteiros, positivos, consecutivos e diferentes de zero.
        Obs.: O ID zero (0) indica que o fornecedor foi exclu�do e a posi�ao � vaga.
*/
void cadastroFornc(FILE *);

/*
    Gera e retorna um ID para o cadastro de um novo fornecedor. Como a fun��o funciona:
        - verifica quantos fornecedores j� est�o cadastrados e retorna como novo ID a quantidade de fornecedores + 1, gerando assim o ID para o novo fornecedor.
        - a cada loop a fun��o verifica se o ID corrente � igual a 0 (indica que o fornecedor foi exclu�do), caso seja, retorna a quantidade de fornecedores verificados at� o momento + 1.

        Par�metros: ponteiro FILE que recebe o endereco de mem�ria do arquivo 'fornecedor.dat'.
        retornos: o ID novo ou reutilizado.
*/
unsigned long novoIdFornc(FILE *);

/*
    Mostra o menu de Altera��o, ele possui as op��es de alterar e excluir. A fun��o simplesmente verifica se h� fornecedores cadastrados,
    permite a escolha de uma das op��es, faz a valida��o e chama a fun��o correspondente.
        Par�metros: ponteiro FILE que recebe o endereco de mem�ria do arquivo 'fornecedor.dat'.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void menuAlterarFornc(FILE *);

/*
    Permite a altera��o de alguns dados do fornecedor. Chama a fun��o que consulta o ID (entrada),
    printa os dados antigos do fornecedor e permite a sua altera��o (caso o fornecedor exista).
*/
void alterarFornc(FILE *);

/*
    Permite a exclus�o do fornecedor. Chama a fun��o que consulta o ID (entrada),
    printa os dados do fornecedor e permite a sua exclus�o (caso o fornecedor exista).
        Exclus�o: atribuir 0 ao campo do ID.
*/
void excluirFornc(FILE *);

/*
    Mostra o menu de Consulta com todas as suas op��es. Verifica se h� fornecedores cadastrados, permite a escolha de uma das op��es,
    faz a valida��o e chama a fun��o correspondente.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void menuConsultaFornc(FILE *);

/*
    Realiza uma consulta de fornecedor por meio de um ID (entrada). Chama a fun��o pesquisaVendID para verificar se o ID � valido,
    relaiza uma leitura no arquivo 'fornecedor.dat'(utilizando a posi��o recebida pela fun��o chamada anteriormente) armazenando na struct fornecedor
    e imprime os dados do fornecedor, caso exista.
        Pode printar uma mensagem de erro caso o fornecedor n�o exista.
*/
int consultaForncID(FILE *);

/*
    Realiza uma consulta de fornecedor por meio de um CPF(entrada). Chama a fun��o pesquisaForncCPF para verificar se o CPF � valido,
    realiza uma leitura no arquivo 'fornecedor.dat'(utilizando a posi��o recebida pela fun��o chamada anteriormente) armazenando na struct TFornecedor
    e imprime os dados do fornecedor, caso exista.
        Pode printar uma mensagem de erro caso o fornecedor n�o exista.
*/
void consultaForncCNPJ(FILE *);

/*
   Realiza uma consulta de fornecedor por meio de um Prefixo(entrada). Compara o Prefixo com o nome de todos os fornecedores, sempre imprimindo os dados dos
   fornecedores cuja compara��o retorne 0.
        Pode printar uma mensagem de erro caso nenhuma compara��o retorne 0.
*/
void consultaForncNome(FILE *);

/*
    Imprime os dados de todos os fornecedores cadastrados. Verifica se h� fornecedores cadastrados, posiciona o indicador de posi��o no come�o do arquivo 'fornecedor.dat'
    e percorre todo o arquivo, imprimindo os dados com a fun��o printTFornc.
*/
void listagemFornc(FILE *);

/*
    Verifica se o fornecedor com o ID recebido por par�metro existe. Retorna a sua posi��o caso exista ou -1 caso n�o.
        Par�metros: unsigned long para o ID, ponteiro FILE para o arquivo 'fornecedor.dat'.
        Retorno: posi��o dos dados do fornecedor ou -1 (inexistente).
*/
int pesquisaForncID(FILE *, unsigned long);

/*
    Verifica se o fornecedor com o CPF recebido por par�metro existe. Retorna a sua posi��o caso exista ou -1 caso n�o.
        Par�metros: char[] para o CPF, ponteiro FILE para o arquivo 'fornecedor.dat'.
        Retorno: posi��o dos dados do fornecedor ou -1 (inexistente).
*/
int pesquisaForncCNPJ(FILE *, char *);

/*
    Verifica se o fornecedor com o EMAIL recebido por par�metro existe. Retorna a sua posi��o caso exista ou -1 caso n�o.
        Par�metros: char[] para o email, ponteiro FILE para o arquivo 'fornecedor.dat'.
        Retorno: posi��o dos dados do fornecedor ou -1 (inexistente).
*/
int pesquisaForncNome(FILE *, char *);

/*
    Printa na tela todos os dados da Struct recebida por par�metro.
*/
void printTFornc(TFornecedor);

/*
Recebe uma posi��o (arquivo "fornecedor.dat") e retorna o id do fornecedor armazenado na mesma.
*/
unsigned long getIDFornecedor(FILE *, int);

/*
Recebe um id e armazena na vari�vel char * o nome do fornecedor correspondente.
*/
void getNomeFornecedor(unsigned long, char *);
#endif /*FORNECEDOR_H_INCLUDED*/
