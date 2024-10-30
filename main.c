/*
    Inês Sofia Fernandes Carvalho
    2017015276
    Trabalho Prático - Metro Mondego
*/

#include "paragens.h"
#include "linhas.h"

int main()
{
    int totalParagens = 0, opcao;
    paragem *paragens = NULL;
    plinha lista = NULL;


    paragens=carregaParagens(&totalParagens);
    lista=carregaLista();

    printf("\t\tBem Vindo ao Metro Mondego!!\n");
    do {
        printf("\n\t\t======== MENU ========\n");
        printf("\t\t1. Mostrar Paragens\n");
        printf("\t\t2. Registar Paragens\n");
        printf("\t\t3. Eliminar Paragens\n");
        printf("\t\t4. Mostrar Linhas\n");
        printf("\t\t5. Atualizar Linhas\n");
        printf("\t\t6. Adicionar Linha - Manualmente\n");
        printf("\t\t7. Adicionar Linha - Ficheiro\n");
        printf("\t\t8. Eliminar Linha\n");
        printf("\t\t9. Calculo de Percursos\n");
        printf("\t\t0. Sair\n");
        printf("\t\t=======================\n");

        printf("\t\tEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mostraParagens(paragens,totalParagens);
                break;
            case 2:
                paragens=registaParagem(paragens,&totalParagens);
                break;
            case 3:
                eliminaParagem(paragens,&totalParagens);
                break;
            case 4:
                mostrarLinhas(lista);
                break;
            case 5:
                lista=atualizarLinha(lista);
                break;
            case 6:
                lista = adicionarLinhaManualmente(lista);
                break;
            case 7:
                lista=adicionarLinhaPorFicheiro(lista);
                break;
            case 8:
                eliminarLinha(lista);
                break;
            case 9:
                calculaPercursos(lista);
                break;
            case 0:
                printf("Sair\n");
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    } while (opcao != 0);

    guardarParagens(paragens,&totalParagens);
    guardarLinhas(lista);

    free(paragens);
    freeLista(lista);
    return 0;
}
