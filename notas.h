#ifndef NOTAS_H_INCLUDED
#define NOTAS_H_INCLUDED

/*Biblioteca com as fun��es de manipula��o das notas e itemNota de compra e venda(fiscal)*/

/*======================NOTA FISCAL======================*/
typedef struct{
    unsigned long id, idCliente, idVendedor;
    char dataCompra[11];
    float ValorTotal;
}TNotaFiscal;

typedef struct{
    unsigned long id, idNotaFiscal, idProduto;
    float valorVenda;
    unsigned int quantidade;
}TItemNotaFiscal;

/*======================NOTA COMPRA======================*/
typedef struct{
    unsigned long id, idFornecedor;
    char dataCompra[11];
    float valorTotal;
}TNotaCompra;

typedef struct{
    unsigned long id, idProduto, idNotaCompra;
    unsigned int quantidade;
    float valorUnitario;
}TItemNotaCompra;


/*======================NOTA FISCAL======================*/
/*
Cria e armazena uma nova Nota Fiscal no arquivo "notaFiscal.dat".
    Utiliza os dados recebidos por par�metro para criar a nova Nota.
    Retorno: o ID da nova nota ou 0 caso n�o consiga abrir/criar o arquivo.
*/
unsigned long novaNotaFiscal(unsigned long idVendedor, unsigned long idCliente, char *data, float valTotal);

/*
Gera e retorna um ID para a nova nota Fiscal. Como a fun��o funciona:
    - verifica quantas notas existem e retorna como novo ID a quantidade de notas + 1, gerando assim o ID para a nova nota.
    Retorno: o ID novo.
*/
unsigned long novoIdNotaFiscal(FILE *arq);

/*
Cria e armazena um novo item Nota Fiscal no arquivo "itemNotaFiscal.dat".
    Utiliza os dados recebidos por par�metro para criar o novo Item.
*/
void novoItemNotaFiscal(unsigned long idProduto, unsigned long idNotaFiscal, unsigned long quantidade, float valVenda);

/*
Gera e retorna um ID para o novo item nota Fiscal. Como a fun��o funciona:
    - verifica quantos itens existem e retorna como novo ID a quantidade de itens + 1, gerando assim o ID para o novo item.
    Retorno: o ID novo.
*/
unsigned long novoIdItemNotaFiscal(FILE *arq);

/*
Recebe um ID, retorna os dados da nota Fiscal com esse ID (por ponteiro).
    retorno: 1 caso a nota exista, 0 caso n�o exista
*/
int getNotaFiscal(unsigned long, TNotaFiscal*);

/*
Printa os dados dos Itens que pertencem � nota Fiscal (ID recebido por par�metro).
    Pode printar na tela caso o par�metro 1 seja NULL ou em determinado arquivo caso n�o seja.
*/
void printaItemNotaFiscal(FILE *, unsigned long);


/*======================NOTA COMPRA======================*/
/*
Cria e armazena uma nova Nota Compra no arquivo "notaCompra.dat".
    Utiliza os dados recebidos por par�metro para criar a nova Nota.
    Retorno: o ID da nova nota ou 0 caso n�o consiga abrir/criar o arquivo.
*/
unsigned long novaNotaCompra(unsigned long, char *, float);

/*
Gera e retorna um ID para a nova nota Compra. Como a fun��o funciona:
    - verifica quantas notas existem e retorna como novo ID a quantidade de notas + 1, gerando assim o ID para a nova nota.
    Retorno: o ID novo.
*/
unsigned long novoIdNotaCompra(FILE *);

/*
Cria e armazena um novo item Nota Compra no arquivo "itemNotaCompra.dat".
    Utiliza os dados recebidos por par�metro para criar o novo Item.
*/
void novoItemNotaCompra(unsigned long, unsigned long, unsigned long, float);

/*
Gera e retorna um ID para o novo item nota Compra. Como a fun��o funciona:
    - verifica quantos itens existem e retorna como novo ID a quantidade de itens + 1, gerando assim o ID para o novo item.
    Retorno: o ID novo.
*/
unsigned long novoIdItemNotaCompra(FILE *);

/*
Recebe um ID, retorna os dados da nota Compra com esse ID (por ponteiro).
    retorno: 1 caso a nota exista, 0 caso n�o exista
*/
int getNotaCompra(unsigned long, TNotaCompra *);

/*
Printa os dados dos Itens que pertencem � nota Compra (ID recebido por par�metro).
    Pode printar na tela caso o par�metro 1 seja NULL ou em determinado arquivo caso n�o seja.
*/
void printaItemNotaCompra(FILE *,unsigned long);


/*=====================VERIFICADORES=====================*/
/*
Verifica se existem notas Fiscais relacionadas com o vendedor selecionado (par�metro id).
O id se junta � outro verificador: data espec�fica ou m�s.
Condi��es dos par�metros:
    Somente verificar: par�metro printa = 0.
    Verificar/printar usando a data: par�metro mes = 0.
    verificar/printar usando o m�s:  par�metro data = "NULL".
    Printar em tela: par�metro printa = 1 e arqUser = NULL.
    Printar em arquivo: par�metro printa = 1 e arqUser = Nome do Arquivo.

    Retorno: 1 caso encontre uma nota e 0 caso n�o encontre.

*/
int verificaVendDataNotaFiscal(unsigned int, char *, int, int, FILE *);

/*
Verifica se existem notas Fiscais relacionadas com o cliente selecionado (par�metro id) e que foram emitidas em uma data espec�fica.
Condi��es dos par�metros:
    Somente verificar: par�metro printa = 0.
    Printar em tela: par�metro printa = 1 e arqUser = NULL.
    Printar em arquivo: par�metro printa = 1 e arqUser = Nome do Arquivo.

    Retorno: 1 caso encontre uma nota e 0 caso n�o encontre.

*/
int verificaClienteDataNotaFiscal(unsigned int, char *, int, FILE *);

/*
Verifica se existem notas Fiscais relacionadas com o cliente selecionado (par�metro id) e que foram emitidas entre um determinado intervalo de datas.
Condi��es dos par�metros:
    Somente verificar: par�metro printa = 0.
    Printar em tela: par�metro printa = 1 e arqUser = NULL.
    Printar em arquivo: par�metro printa = 1 e arqUser = Nome do Arquivo.

    Retorno: 1 caso encontre uma nota e 0 caso n�o encontre.

*/
int verificaClienteIntervaloNotaFiscal(unsigned int, char *, char *, int, FILE *);

/*
Calcula o valor em vendas de cada vendedor e retorna o maior deles.
Pode ser calculado utilizando um m�s ou um intervalo de datas como par�metros.
Condi��es dos par�metros:
    Somente verificar: par�metro printa = 0.
    Verificar usando a data: par�metro mes = 0.
    verificar usando o m�s:  par�metros dataMaior e dataMenor iguais � "NULL".

    Retorno: o maior valor em vendas encontrado, sem o seu vendedor.

*/
float verificaMaiorValorVendas(int, char *, char *);

/*
Verifica se o valor em vendas de cada vendedor � igual ao valor passado por par�metro (maior valor em vendas),
caso seja, printa alguns dos respectivos vendedores.
Pode ser calculado utilizando um m�s ou um intervalo de datas como par�metros.
Condi��es dos par�metros:
    Verificar usando a data: par�metro mes = 0.
    verificar usando o m�s:  par�metros dataMaior e dataMenor iguais � "NULL".
    Printar em tela: par�metro arqUser = NULL.
    Printar em arquivo: par�metro arqUser = Nome do Arquivo.
*/
void printaVendMaiorValorVendas(float, int, char *, char *, FILE *);

#endif /*NOTAS_H_INCLUDED*/
