#ifndef RELATORIOS_H_INCLUDED
#define RELATORIOS_H_INCLUDED

/*
Menu com todas as op��es de relat�rios.
    Permite a escolha de um deles, bem como a escolha do tipo de impress�o (em tela ou em arquivo).
    Chama as demais fun��es de relat�rios.
*/
void areaRelatorios();

/*
Permite a escolha de um ID de Nota Fiscal, verifica se ela existe, imprime seus dados e os dados de seus respectivos itens para o usu�rio.
    O par�metro tipo define se o relat�rio ser� imprimido na tela ou em arquivo.
*/
void relatorioNotaFiscal(int);

/*
Permite a escolha de um ID de Nota Compra, verifica se ela existe, imprime seus dados e os dados de seus respectivos itens para o usu�rio.
    O par�metro tipo define se o relat�rio ser� imprimido na tela ou em arquivo.
*/
void relatorioNotaCompra(int);

/*
Permite a escolha de um ID de Cliente e de uma data, verifica se existe alguma nota correspondente, imprime seus dados e os dados de seus respectivos itens para o usu�rio.
    O par�metro tipo define se o relat�rio ser� imprimido na tela ou em arquivo.
*/
void relatorioComprasClienteData(int);

/*
Permite a escolha de um ID de Cliente e de duas datas (intervalo), verifica se existe alguma nota correspondente, imprime seus dados e os dados de seus respectivos itens para o usu�rio.
    O par�metro tipo define se o relat�rio ser� imprimido na tela ou em arquivo.
*/
void relatorioComprasClienteIntervalo(int);

/*
Permite a escolha de um ID de Vendedor e de uma data, verifica se existe alguma nota correspondente, imprime seus dados e os dados de seus respectivos itens para o usu�rio.
    O par�metro tipo define se o relat�rio ser� imprimido na tela ou em arquivo.
*/
void relatorioVendasVendedorDia(int);

/*
Permite a escolha de um ID de Vendedor e de um m�s, verifica se existe alguma nota correspondente, imprime seus dados e os dados de seus respectivos itens para o usu�rio.
    O par�metro tipo define se o relat�rio ser� imprimido na tela ou em arquivo.
*/
void relatorioVendasVendedorMes(int);

/*
Permite a escolha de um determinado m�s, realiza calc�los para saber qual foi o maior valor em Vendas (separado por vendedor) nesse mesmo m�s
e imprime os dados do vendedor(es) que alcan�ou esse esse valor em vendas.
    O par�metro tipo define se o relat�rio ser� imprimido na tela ou em arquivo.
*/
void relatorioMaiorValorVendedorMes(int);

/*
Permite a escolha de um intervalo de datas, realiza calc�los para saber qual foi o maior valor em Vendas (separado por vendedor) nesse intervalo
e imprime os dados do vendedor(es) que alcan�ou esse esse valor em vendas.
    O par�metro tipo define se o relat�rio ser� imprimido na tela ou em arquivo.
*/
void relatorioMaiorValorVendedorIntervalo(int);

/*
Permite a escolha de um ID de Produto, verifica se ele existe e imprime todo o seu hist�rico de altera��o de pre�o.
    O par�metro tipo define se o relat�rio ser� imprimido na tela ou em arquivo.
*/
void relatorioHistorico(int);

/*
Permite a entrada de um nome para o arquivo, adiciona a extens�o '.txt' e cria/abre um arquivo utilizando esse nome.
    Retorna o endere�o do arquivo aberto por ponteiro.
*/
void criaTXT(FILE **);

/*
Recebe o n�mero correspondente a determinado m�s e retorna o seu nome.
*/
void getNomeMes(int, char *);

#endif /*RELATORIOS_H_INCLUDED*/
