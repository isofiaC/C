/*
    Inês Sofia Fernandes Carvalho
    2017015276
    Trabalho Prático - Metro Mondego
*/

#ifndef PARAGENS_H
#define PARAGENS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

//Estrutura para armazenar as paragens
struct paragem{
    char nomeParagem [TAM];
    char codigoParagem [5];
};

typedef struct paragem paragem;

//Visualizar as paragens
void mostraParagens (paragem *paragens, int total);

//Guardar as paragens
void guardarParagens (paragem *paragens, int *total);

//Carrega as paragens
paragem * carregaParagens (int * total);

//Regista uma paragem
paragem * registaParagem(paragem * paragens, int *total);

//Eliminar uma paragem
void  eliminaParagem(paragem * paragens, int *total);
#endif // PARAGENS_H
