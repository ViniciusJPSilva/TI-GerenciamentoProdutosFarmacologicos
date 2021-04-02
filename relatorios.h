#ifndef RELATORIOS_H_INCLUDED
#define RELATORIOS_H_INCLUDED

/*
Menu com todas as opções de relatórios.
    Permite a escolha de um deles, bem como a escolha do tipo de impressão (em tela ou em arquivo).
    Chama as demais funções de relatórios.
*/
void areaRelatorios();

/*
Permite a escolha de um ID de Nota Fiscal, verifica se ela existe, imprime seus dados e os dados de seus respectivos itens para o usuário.
    O parâmetro tipo define se o relatório será imprimido na tela ou em arquivo.
*/
void relatorioNotaFiscal(int);

/*
Permite a escolha de um ID de Nota Compra, verifica se ela existe, imprime seus dados e os dados de seus respectivos itens para o usuário.
    O parâmetro tipo define se o relatório será imprimido na tela ou em arquivo.
*/
void relatorioNotaCompra(int);

/*
Permite a escolha de um ID de Cliente e de uma data, verifica se existe alguma nota correspondente, imprime seus dados e os dados de seus respectivos itens para o usuário.
    O parâmetro tipo define se o relatório será imprimido na tela ou em arquivo.
*/
void relatorioComprasClienteData(int);

/*
Permite a escolha de um ID de Cliente e de duas datas (intervalo), verifica se existe alguma nota correspondente, imprime seus dados e os dados de seus respectivos itens para o usuário.
    O parâmetro tipo define se o relatório será imprimido na tela ou em arquivo.
*/
void relatorioComprasClienteIntervalo(int);

/*
Permite a escolha de um ID de Vendedor e de uma data, verifica se existe alguma nota correspondente, imprime seus dados e os dados de seus respectivos itens para o usuário.
    O parâmetro tipo define se o relatório será imprimido na tela ou em arquivo.
*/
void relatorioVendasVendedorDia(int);

/*
Permite a escolha de um ID de Vendedor e de um mês, verifica se existe alguma nota correspondente, imprime seus dados e os dados de seus respectivos itens para o usuário.
    O parâmetro tipo define se o relatório será imprimido na tela ou em arquivo.
*/
void relatorioVendasVendedorMes(int);

/*
Permite a escolha de um determinado mês, realiza calcúlos para saber qual foi o maior valor em Vendas (separado por vendedor) nesse mesmo mês
e imprime os dados do vendedor(es) que alcançou esse esse valor em vendas.
    O parâmetro tipo define se o relatório será imprimido na tela ou em arquivo.
*/
void relatorioMaiorValorVendedorMes(int);

/*
Permite a escolha de um intervalo de datas, realiza calcúlos para saber qual foi o maior valor em Vendas (separado por vendedor) nesse intervalo
e imprime os dados do vendedor(es) que alcançou esse esse valor em vendas.
    O parâmetro tipo define se o relatório será imprimido na tela ou em arquivo.
*/
void relatorioMaiorValorVendedorIntervalo(int);

/*
Permite a escolha de um ID de Produto, verifica se ele existe e imprime todo o seu histórico de alteração de preço.
    O parâmetro tipo define se o relatório será imprimido na tela ou em arquivo.
*/
void relatorioHistorico(int);

/*
Permite a entrada de um nome para o arquivo, adiciona a extensão '.txt' e cria/abre um arquivo utilizando esse nome.
    Retorna o endereço do arquivo aberto por ponteiro.
*/
void criaTXT(FILE **);

/*
Recebe o número correspondente a determinado mês e retorna o seu nome.
*/
void getNomeMes(int, char *);

#endif /*RELATORIOS_H_INCLUDED*/
