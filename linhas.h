/*
    Inês Sofia Fernandes Carvalho
    2017015276
    Trabalho Prático - Metro Mondego
*/

#ifndef LINHAS_H
#define LINHAS_H
#define TAM 100
#include "paragens.h"

//Estrutura para armazenar as linhas
typedef struct linhas {
    char nomeLinha[TAM];
    int numParagens;
    struct paragem* paragens;
    struct linhas* prox;
} linhas;

typedef linhas* plinha;

//preenche um nó da lista ligada
void preenche_info(plinha novo);

//adiciona um novo nó no fim da lista
plinha adicionarLinhaManualmente(plinha p);

//mostra a informacao das linhas
void mostrarLinhas(plinha p);

//Guarda a lista ligada das linhas e respetivas paragens
void guardarLinhas(plinha lista);

//Carregar a lista ligada das linhas e respetivas paragens
plinha carregaLista();

//Libertar a memoria da lista ligada
void freeLista(plinha p);

//Elimina uma linha o metro da lista ligada
void eliminarLinha(plinha p);

//Atualiza uma linha
plinha atualizarLinha(plinha p);

//Adiciona linha a partir de um ficheiro
plinha adicionarLinhaPorFicheiro(plinha p);

//Calcula percursos entre duas paragens
void calculaPercursos(plinha lista);
#endif // LINHAS_H
