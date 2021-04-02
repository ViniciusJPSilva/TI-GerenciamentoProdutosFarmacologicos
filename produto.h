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
    Permite que o usuário cadastre um novo produto, validando cada entrada. Ao final, armazena os dados no arquivo 'produto.dat'.
        Novos IDs: os IDs dos produtos são predefinidos pela função novoIdProduto(), são todos inteiros, positivos, consecutivos e diferentes de zero.
*/
void cadastroProduto();

/*
    Gera e retorna um ID para o cadastro de um novo produto. Como a função funciona:
        - verifica quantos produtos já estão cadastrados e retorna como novo ID a quantidade de produtos + 1, gerando assim o ID para o novo produto.

        Parâmetros: ponteiro FILE que recebe o endereco de memória do arquivo 'produto.dat'.
        retornos: o ID novo.
*/
unsigned long novoIdProduto(FILE *);

/*
    Mostra o menu de Atualização de Preços, ele possui as opções de atualizar o preço de todos ou somente um produto. A função simplesmente verifica se há produto cadastrados,
    permite a escolha de uma das opções, faz a validação e chama a função correspondente.
        Parâmetros: ponteiro FILE que recebe o endereco de memória do arquivo 'produto.dat'.
        Printa na tela uma mensagem de erro caso o arquivo esteja vazio.
*/
void attPrecoProduto();

/*
    Atualiza o preço unitário de todos os produtos em determinada porcentagem (%), podendo aumentar ou diminuir o valor original.
    A função também armazena as alterações no arquivo "HistoricoPreco.dat".
*/
void attPrecoTodos(FILE *, FILE *);

/*
    Atualiza o preço unitário de um determinado produto em determinada porcentagem (%), podendo aumentar ou diminuir o valor original.
    A função também armazena a alteração no arquivo "HistoricoPreco.dat".
*/
void attPrecoUnico(FILE *, FILE *);

/*
    Verifica se o usuário quer atualizar o preço aumentando ou diminuindo o valor original
*/
int tipoAttPreco();

/*
    Recebe e valida uma Procentagem (float) fornecido pelo do usuário
*/
float entradaPorcentagem();

/*
    Realiza uma consulta de produto por meio de um ID (entrada). Chama a função pesquisaProdutoID para verificar se o ID é valido,
    reliza uma leitura no arquivo 'produto.dat'(utilizando a posição recebida pela função chamada anteriormente) armazenando na struct produto
    e imprime os dados do produto, caso exista.
        Pode printar uma mensagem de erro caso o produto não exista.
*/
int consultaProdutoID(FILE *);

/*
    Verifica se o produto com o ID recebido por parâmetro existe. Retorna a sua posição caso exista ou -1 caso não.
        Parâmetros: unsigned long para o ID, ponteiro FILE para o arquivo 'produto.dat'.
        Retorno: posição dos dados do produto ou -1 (inexistente).
*/
int pesquisaProdutoID(FILE *, unsigned long);

/*
    Imprime os dados de todos os produtos cadastrados. Verifica se há produtos cadastrados, posiciona o indicador de posição no começo do arquivo 'produto.dat'
    e percorre todo o arquivo, imprimindo os dados com a função printTProduto.
*/
void listagemProdutos(FILE *);

/*
    Printa na tela todos os dados da Struct recebida por parâmetro.
*/
void printTProduto(TProduto);

/*
    Recebe uma posição (arquivo "produto.dat") e retorna o id do produto armazenado nessa mesma posição.
*/
unsigned long getIDProduto(FILE *, int);

/*
    Verifica a quantidade de itens em estoque de um determinado produto. A função recebe o arquivo 'produto.dat' e o id do produto que se deseja verificar o estoque.
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
Recebe um id para identificar o produto e uma quantidade que será adicionada (incrementada) à quantidade já existente.
*/
void atualizaEstoque(FILE *, unsigned long, int);

/*
Realiza uma atualização do arquivo "HistoricoPreco.dat", para futuros relatórios
    Monta uma struct tipo THistorico utilizando os dados do TProduto recebido e armazena esses dados no arquivo "historicoPreco".
*/
void atualizaHistorico(FILE *, TProduto);

/*
Verifica se existe ou Printa/imprime na tela ou em algum arquivo .txt todos os históricos de preço de um determinado produto (id recebido por parâmetro).
    Printa a data de alteração seguida do valor alterado (novo valor atribuído ao produto).
*/
int printaHistorico(FILE *,unsigned long, int);

#endif /*PRODUTO_H_INCLUDED*/




