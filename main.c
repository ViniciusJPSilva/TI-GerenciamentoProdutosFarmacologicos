/*
    Segundo Trabalho Pr�tico
    Curso: T�cnico em Inform�tica
    Disciplina: L�gica de Programa��o II
    Prof. Wender Magno Cota
    Aluno: Vin�cius Jos� Pires Silva
*/

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "entradaSaida.h"
#include "cliente.h"
#include "vendedor.h"
#include "fornecedor.h"
#include "produto.h"
#include "compra.h"
#include "relatorios.h"

int main(){
    int opcao, invalido;

    setlocale(LC_ALL, "portuguese");

    do{
        /*Menu Principal chamada dos submenus*/
        printLogo();
        printMenuOption();
        do{
            printf("\n\tEscolha uma op��o: ");
            scanf("%d", &opcao);

            invalido = 0;
            switch(opcao){
            case 1:
                areaCliente();
                break;
            case 2:
                areaVendedor();
                break;
            case 3:
                areaFornecedor();
                break;
            case 4:
                cadastroProduto();
                break;
            case 5:
                compraEvenda(1);
                break;
            case 6:
                compraEvenda(2);
                break;
            case 7:
                attPrecoProduto();
                break;
            case 8:
                areaRelatorios();
                break;
            case 9:
                printf("\n\n\tFINALIZANDO...\n\n");
                break;
            default:
                invalido = 1;
            }

            if(invalido)
                printInvOption("Op��o");

        }while(invalido);
    }while (opcao != 9);

    return 0;
}


