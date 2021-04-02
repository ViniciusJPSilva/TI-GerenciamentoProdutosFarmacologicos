#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

typedef struct{
    unsigned long id;
    char nome[100];
    unsigned int quantidadeEstoque;
    float precoUnitario;
}TProduto;

typedef struct{
    unsigned long idProduto;
    char dataAlteracao[11];
    float valor;
}THistorico;

/*
    Permite que o usu�rio cadastre um novo produto, validando cada entrada. Ao final, armazena os dados no arquivo 'produto.dat'.
        Novos IDs: os IDs dos produtos s�o predefinidos pela fun��o novoIdProduto(), s�o todos inteiros, positivos, consecutivos e diferentes de zero.
*/
void cadastroProduto();

/*
    Gera e retorna um ID para o cadastro de um novo produto. Como a fun��o funciona:
        - verifica quantos produtos j� est�o cadastrados e retorna como novo ID a quantidade de produtos + 1, gerando assim o ID para o novo produto.

        Par�metros: ponteiro FILE que recebe o endereco de mem�ria do arquivo 'produto.dat'.
        retornos: o ID novo.
*/
unsigned long novoIdProduto(FILE *);

/*
    Mostra o menu de Atualiza��o de Pre�os, ele possui as op��es de atualizar o pre�o de todos ou somente um produto. A fun��o simplesmente verifica se h� produto cadastrados,
    permite a escolha de uma das op��es, faz a valida��o e chama a fun��o correspondente.
        Par�metros: ponteiro FILE que recebe o endereco de mem�ria do arquivo 'produto.dat'.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void attPrecoProduto();

/*
    Atualiza o pre�o unit�rio de todos os produtos em determinada porcentagem (%), podendo aumentar ou diminuir o valor original.
    A fun��o tamb�m armazena as altera��es no arquivo "HistoricoPreco.dat".
*/
void attPrecoTodos(FILE *, FILE *);

/*
    Atualiza o pre�o unit�rio de um determinado produto em determinada porcentagem (%), podendo aumentar ou diminuir o valor original.
    A fun��o tamb�m armazena a altera��o no arquivo "HistoricoPreco.dat".
*/
void attPrecoUnico(FILE *, FILE *);

/*
    Verifica se o usu�rio quer atualizar o pre�o aumentando ou diminuindo o valor original
*/
int tipoAttPreco();

/*
    Recebe e valida uma Procentagem (float) fornecido pelo do usu�rio
*/
float entradaPorcentagem();

/*
    Realiza uma consulta de produto por meio de um ID (entrada). Chama a fun��o pesquisaProdutoID para verificar se o ID � valido,
    reliza uma leitura no arquivo 'produto.dat'(utilizando a posi��o recebida pela fun��o chamada anteriormente) armazenando na struct produto
    e imprime os dados do produto, caso exista.
        Pode printar uma mensagem de erro caso o produto n�o exista.
*/
int consultaProdutoID(FILE *);

/*
    Verifica se o produto com o ID recebido por par�metro existe. Retorna a sua posi��o caso exista ou -1 caso n�o.
        Par�metros: unsigned long para o ID, ponteiro FILE para o arquivo 'produto.dat'.
        Retorno: posi��o dos dados do produto ou -1 (inexistente).
*/
int pesquisaProdutoID(FILE *, unsigned long);

/*
    Imprime os dados de todos os produtos cadastrados. Verifica se h� produtos cadastrados, posiciona o indicador de posi��o no come�o do arquivo 'produto.dat'
    e percorre todo o arquivo, imprimindo os dados com a fun��o printTProduto.
*/
void listagemProdutos(FILE *);

/*
    Printa na tela todos os dados da Struct recebida por par�metro.
*/
void printTProduto(TProduto);

/*
    Recebe uma posi��o (arquivo "produto.dat") e retorna o id do produto armazenado nessa mesma posi��o.
*/
unsigned long getIDProduto(FILE *, int);

/*
    Verifica a quantidade de itens em estoque de um determinado produto. A fun��o recebe o arquivo 'produto.dat' e o id do produto que se deseja verificar o estoque.
        retorna a quantidade em estoque do produto desejado.
        Obs.: retorna 0 tanto para 0 produtos em estoque quanto para produto inexistente
*/
unsigned int getEstoqueProduto(FILE *, unsigned long);

/*
    Recebe um id de um produto, verifica todo o arquivo "produto.dat" e retorna o valor do produto que possui este id.
*/
float getValorProduto(FILE *, unsigned long);

/*
    Recebe um id de um produto, verifica todo o arquivo "produto.dat" e retorna (ponteiro) o nome do produto que possui este id.
*/
void getNomeProduto(unsigned long, char *);

/*
Atualiza o campo quantidadeEstoque de um produto.
Recebe um id para identificar o produto e uma quantidade que ser� adicionada (incrementada) � quantidade j� existente.
*/
void atualizaEstoque(FILE *, unsigned long, int);

/*
Realiza uma atualiza��o do arquivo "HistoricoPreco.dat", para futuros relat�rios
    Monta uma struct tipo THistorico utilizando os dados do TProduto recebido e armazena esses dados no arquivo "historicoPreco".
*/
void atualizaHistorico(FILE *, TProduto);

/*
Verifica se existe ou Printa/imprime na tela ou em algum arquivo .txt todos os hist�ricos de pre�o de um determinado produto (id recebido por par�metro).
    Printa a data de altera��o seguida do valor alterado (novo valor atribu�do ao produto).
*/
int printaHistorico(FILE *,unsigned long, int);

#endif /*PRODUTO_H_INCLUDED*/




