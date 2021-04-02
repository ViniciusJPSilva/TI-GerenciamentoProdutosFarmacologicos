#ifndef FORNECEDOR_H_INCLUDED
#define FORNECEDOR_H_INCLUDED

typedef struct{
    unsigned long id;
    char nome[100], cnpj[15], email[50], telefone[15];
}TFornecedor;

/*
    Abre/cria um arquivo 'fornecedor.dat', mostra o menu de manutenção dos fornecedores e, com a entrada da opção, chama a função checkOpcaoFornc.
        Printa na tela uma mensagem de erro caso não consiga abrir o arquivo.
*/
void areaFornecedor();

/*
    Permite que o usuário cadastre um novo fornecedor, validando cada entrada. Ao final, armazena os dados no arquivo 'fornecedor.dat'.
        Novos IDs: os IDs dos fornecedores são predefinidos pela função novoIdFornc(), são todos inteiros, positivos, consecutivos e diferentes de zero.
        Obs.: O ID zero (0) indica que o fornecedor foi excluído e a posiçao é vaga.
*/
void cadastroFornc(FILE *);

/*
    Gera e retorna um ID para o cadastro de um novo fornecedor. Como a função funciona:
        - verifica quantos fornecedores já estão cadastrados e retorna como novo ID a quantidade de fornecedores + 1, gerando assim o ID para o novo fornecedor.
        - a cada loop a função verifica se o ID corrente é igual a 0 (indica que o fornecedor foi excluído), caso seja, retorna a quantidade de fornecedores verificados até o momento + 1.

        Parâmetros: ponteiro FILE que recebe o endereco de memória do arquivo 'fornecedor.dat'.
        retornos: o ID novo ou reutilizado.
*/
unsigned long novoIdFornc(FILE *);

/*
    Mostra o menu de Alteração, ele possui as opções de alterar e excluir. A função simplesmente verifica se há fornecedores cadastrados,
    permite a escolha de uma das opções, faz a validação e chama a função correspondente.
        Parâmetros: ponteiro FILE que recebe o endereco de memória do arquivo 'fornecedor.dat'.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void menuAlterarFornc(FILE *);

/*
    Permite a alteração de alguns dados do fornecedor. Chama a função que consulta o ID (entrada),
    printa os dados antigos do fornecedor e permite a sua alteração (caso o fornecedor exista).
*/
void alterarFornc(FILE *);

/*
    Permite a exclusão do fornecedor. Chama a função que consulta o ID (entrada),
    printa os dados do fornecedor e permite a sua exclusão (caso o fornecedor exista).
        Exclusão: atribuir 0 ao campo do ID.
*/
void excluirFornc(FILE *);

/*
    Mostra o menu de Consulta com todas as suas opções. Verifica se há fornecedores cadastrados, permite a escolha de uma das opções,
    faz a validação e chama a função correspondente.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void menuConsultaFornc(FILE *);

/*
    Realiza uma consulta de fornecedor por meio de um ID (entrada). Chama a função pesquisaVendID para verificar se o ID é valido,
    relaiza uma leitura no arquivo 'fornecedor.dat'(utilizando a posição recebida pela função chamada anteriormente) armazenando na struct fornecedor
    e imprime os dados do fornecedor, caso exista.
        Pode printar uma mensagem de erro caso o fornecedor não exista.
*/
int consultaForncID(FILE *);

/*
    Realiza uma consulta de fornecedor por meio de um CPF(entrada). Chama a função pesquisaForncCPF para verificar se o CPF é valido,
    realiza uma leitura no arquivo 'fornecedor.dat'(utilizando a posição recebida pela função chamada anteriormente) armazenando na struct TFornecedor
    e imprime os dados do fornecedor, caso exista.
        Pode printar uma mensagem de erro caso o fornecedor não exista.
*/
void consultaForncCNPJ(FILE *);

/*
   Realiza uma consulta de fornecedor por meio de um Prefixo(entrada). Compara o Prefixo com o nome de todos os fornecedores, sempre imprimindo os dados dos
   fornecedores cuja comparação retorne 0.
        Pode printar uma mensagem de erro caso nenhuma comparação retorne 0.
*/
void consultaForncNome(FILE *);

/*
    Imprime os dados de todos os fornecedores cadastrados. Verifica se há fornecedores cadastrados, posiciona o indicador de posição no começo do arquivo 'fornecedor.dat'
    e percorre todo o arquivo, imprimindo os dados com a função printTFornc.
*/
void listagemFornc(FILE *);

/*
    Verifica se o fornecedor com o ID recebido por parâmetro existe. Retorna a sua posição caso exista ou -1 caso não.
        Parâmetros: unsigned long para o ID, ponteiro FILE para o arquivo 'fornecedor.dat'.
        Retorno: posição dos dados do fornecedor ou -1 (inexistente).
*/
int pesquisaForncID(FILE *, unsigned long);

/*
    Verifica se o fornecedor com o CPF recebido por parâmetro existe. Retorna a sua posição caso exista ou -1 caso não.
        Parâmetros: char[] para o CPF, ponteiro FILE para o arquivo 'fornecedor.dat'.
        Retorno: posição dos dados do fornecedor ou -1 (inexistente).
*/
int pesquisaForncCNPJ(FILE *, char *);

/*
    Verifica se o fornecedor com o EMAIL recebido por parâmetro existe. Retorna a sua posição caso exista ou -1 caso não.
        Parâmetros: char[] para o email, ponteiro FILE para o arquivo 'fornecedor.dat'.
        Retorno: posição dos dados do fornecedor ou -1 (inexistente).
*/
int pesquisaForncNome(FILE *, char *);

/*
    Printa na tela todos os dados da Struct recebida por parâmetro.
*/
void printTFornc(TFornecedor);

/*
Recebe uma posição (arquivo "fornecedor.dat") e retorna o id do fornecedor armazenado na mesma.
*/
unsigned long getIDFornecedor(FILE *, int);

/*
Recebe um id e armazena na variável char * o nome do fornecedor correspondente.
*/
void getNomeFornecedor(unsigned long, char *);
#endif /*FORNECEDOR_H_INCLUDED*/
