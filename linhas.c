/*
    Inês Sofia Fernandes Carvalho
    2017015276
    Trabalho Prático - Metro Mondego
*/

#include"linhas.h"
//Preenche dados da linha e das suas paragens
void preenche_info(plinha novo){
    int contaParagens=0;

    printf("\n Nome da Linha:");
    scanf(" %99[^\n]",novo->nomeLinha);

    printf("\nQuantas paragens vai ter: ");
    scanf("%d",&novo->numParagens);

    if(novo->numParagens==0){
        novo->paragens = NULL;
        novo->prox = NULL;
    }else{
       novo->paragens = malloc(novo->numParagens * sizeof(paragem));
        if (novo->paragens == NULL) {
            printf("\nErro ao alocar a memoria!\n");
            return;
        }

        while (contaParagens < novo->numParagens) {
            printf("\nNome da Paragem: ");
            scanf(" %[^\n]", novo->paragens[contaParagens].nomeParagem);
            printf("Codigo da Paragem: ");
            scanf(" %[^\n]", novo->paragens[contaParagens].codigoParagem);
            contaParagens++;
        }

        novo->prox = NULL;
    }

}

//adiciona uma nova linha a lista ligada de linhas
plinha adicionarLinhaManualmente(plinha p){
    plinha novo, aux;

    //1.Alocar memoria
    novo = malloc(sizeof(linhas));
    if(novo==NULL){
        printf("\n\n Erro na alocacao de memoria!");
        return p;
    }

    //2. Preencher dados
    preenche_info(novo);

    //3.Insere no fim da lista
    if(p==NULL)//lista vazia, no fica a cabeça
        p=novo;
    else{
        aux=p;

        while(aux->prox !=NULL)
            aux=aux->prox;

        aux->prox=novo;
    }

    return p;
}

//mostra todas as linhas da lista ligada e as suas paragens
void mostrarLinhas(plinha p){
    int i;

    if(p == NULL)
        printf("\n\t Sem linhas para mostrar!\n");

    while(p != NULL){
        printf("\n\n");
        printf("\tNome da Linha: %s\n", p->nomeLinha);
        printf("\tNumero de Paragens: %d\n", p->numParagens);
        printf("\n\n");
        if(p->numParagens==0)
            printf("\tListagem das Paragens: Nao existem paragens para esta linha\n");
        else{
            for(i=0;i<p->numParagens;i++){
                printf("\n\t\t\tNome da Paragem: %s\n",  p->paragens[i].nomeParagem);
                printf("\n\t\t\tCodigo da Paragem: %s\n", p->paragens[i].codigoParagem);
                printf("\n\n");
            }
        }
        p = p->prox;
    }
}

//Guarda as linhas no ficheiro
void guardarLinhas(plinha lista) {
    FILE* f;
    f = fopen("linhas.dat", "wb");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro!\n");
        return;
    }

    plinha aux = lista;
    while (aux != NULL) {
        fwrite(aux->nomeLinha, sizeof(char), TAM, f);
        fwrite(&(aux->numParagens), sizeof(int), 1, f);

        // Escreve paragens
        for (int i = 0; i < aux->numParagens; i++) {
            fwrite(aux->paragens[i].nomeParagem, sizeof(char), TAM, f);
            fwrite(aux->paragens[i].codigoParagem, sizeof(char), 5, f);
        }
        aux = aux->prox;
    }
    fclose(f);
}

//Carrega as linhas a partir do ficheiro
plinha carregaLista() {
    FILE* f;
    f = fopen("linhas.dat", "rb");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro!\n");
        return NULL;
    }

    plinha lista = NULL;
    plinha atual = NULL;

    while (1) {
        plinha novo;
        novo = malloc(sizeof(linhas));
        if (novo == NULL) {
            printf("Erro na alocacao de memoria!\n");
            fclose(f);
            return NULL;
        }
        // Le linha
        if (fread(novo->nomeLinha, sizeof(char), TAM, f) != TAM) {
            free(novo);
            break;
        }
        if (fread(&(novo->numParagens), sizeof(int), 1, f) != 1) {
            free(novo);
            break;
        }
        if (novo->numParagens > 0) {//tem paragens
            novo->paragens = malloc(novo->numParagens * sizeof(struct paragem));
            if (novo->paragens == NULL) {
                printf("Erro na alocacao de memoria!\n");
                free(novo);
                fclose(f);
                return NULL;
            }
            // Le paragens
            for (int i = 0; i < novo->numParagens; i++) {
                if (fread(novo->paragens[i].nomeParagem, sizeof(char), TAM, f) != TAM) {
                    free(novo->paragens);
                    free(novo);
                    fclose(f);
                    return NULL;
                }
                if (fread(novo->paragens[i].codigoParagem, sizeof(char), 5, f) != 5) {
                    free(novo->paragens);
                    free(novo);
                    fclose(f);
                    return NULL;
                }
            }
        } else {//nao tem paragens
            novo->paragens = NULL;
        }
        novo->prox = NULL;

        if (lista == NULL) {//1º no a inserir na lista -> lista e atual a apontar para o mesmo no
            lista = novo;
            atual = novo;
        } else {//ponteiro prox do nó anterior (atual->prox) para apontar para o nó novo e atual para apontar para o novo nó inserido
            atual->prox = novo;
            atual = novo;
        }
    }
    fclose(f);
    return lista;
}

//Liberta memoria da lista ligada
void freeLista(plinha p) {
    plinha aux;

    while (p != NULL) {
        aux = p;
        p = p->prox;

        // Liberar a memória das paragens
        for (int i = 0; i < aux->numParagens; i++) {
            free(aux->paragens[i].nomeParagem);
            free(aux->paragens[i].codigoParagem);
        }
        free(aux->paragens);

        // Liberar a memória do nó atual
        free(aux);
    }
}

//Eliminar uma linhas
void eliminarLinha(plinha lista) {
    if (lista == NULL) {
        printf("Nao existem linhas para eliminar!\n");
        return;
    }

    char nome[TAM];
    printf("\nQual o nome da linha a eliminar: ");
    scanf("%s", nome);

    plinha atual = lista;
    plinha anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->nomeLinha, nome) == 0) {
            // Linha encontrada, remover
            if (anterior == NULL) {
                lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
                //atualizamos o ponteiro prox do nó anterior para apontar para a próxima linha
            }
            free(atual);
            printf("Linha removida!\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Linha nao encontrada!\n");
}

//Atualiza uma linha
//Elimina a linha a alterar e carrega todas as paragens que a nova linha deve ter
// Função para atualizar uma linha do metrô
plinha atualizarLinha(plinha p) {
    plinha linhaAtual = p;
    plinha linhaAnterior = NULL;
    char nomeLinha[TAM];

    printf("\nQual o nome da linha a atualizar: ");
    scanf("%s", nomeLinha);

    // Procurar a linha
    while (linhaAtual != NULL) {
        if (strcmp(linhaAtual->nomeLinha, nomeLinha) == 0) {
            // Remover a linha
            if (linhaAnterior == NULL) {
                p = linhaAtual->prox;
            } else {
                linhaAnterior->prox = linhaAtual->prox;
            }
            free(linhaAtual);
            linhaAtual = NULL;

            // Criar uma nova linha com as paragens atualizadas
            p = adicionarLinhaManualmente(p);

            printf("\nLinha atualizada!\n");
            return p;
        }

        linhaAnterior = linhaAtual;
        linhaAtual = linhaAtual->prox;
    }
    printf("\nLinha não encontrada!\n");
    return p;
}

plinha adicionarLinhaPorFicheiro(plinha p) {
    char nome[TAM];
    printf("\nQual o nome do ficheiro: ");
    scanf("%s", nome);

    FILE* f;
    f = fopen(nome, "r");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro!\n");
        return p;
    }

    char nomeLinha[TAM];
    // Ler o nome da linha
    if (fgets(nomeLinha, TAM, f) == NULL) {
        printf("Erro ao ler linha do ficheiro!\n");
        fclose(f);
        return p;
    }
    // Criar a nova linha
    plinha novaLinha;
    novaLinha = (plinha) malloc(sizeof(linhas));
    strcpy(novaLinha->nomeLinha, nomeLinha);
    novaLinha->numParagens = 0;
    novaLinha->paragens = NULL;
    novaLinha->prox = NULL;

    char linha[TAM];
    char *token;

    // Ler as paragens
    while (fgets(linha, TAM, f) != NULL) {
        char nomeParagem[TAM];
        char codigoParagem [5];

        // Extrair nome da paragem e codigoParagem usando strtok
        token = strtok(linha, "#");//O ponteiro retornado por strtok aponta para a primeira substring (nome da paragem).
        if (token == NULL) {//verifica-se se o ponteiro retornado por strtok é NULL. pode acontecer se não houver mais substrings a serem extraídas.
            printf("Erro ao ler paragens do ficheiro!\n");
            break;
        }
        strcpy(nomeParagem, token);
         //função strtok é chamada novamente passando NULL como primeiro argumento para continuar a partir do ponto anterior

        token = strtok(NULL, "#");
        if (token == NULL) {
            printf("Erro ao ler paragens do ficheiro!\n");
            break;
        }
        strcpy(codigoParagem, strtok(token, " \t\n"));

        novaLinha->numParagens++;
        //copia para o no a paragem
        novaLinha->paragens = realloc(novaLinha->paragens, (novaLinha->numParagens + 1) * sizeof(paragem));
        if (novaLinha->paragens == NULL) {
            printf("\nErro ao alocar a memoria!\n");
            return NULL;
        }
        strcpy(novaLinha->paragens[novaLinha->numParagens-1].nomeParagem, nomeParagem);
        strcpy(novaLinha->paragens[novaLinha->numParagens-1].codigoParagem, codigoParagem);
    }
    // Adicionar a nova linha ao sistema
    if (p == NULL) {
        p = novaLinha;
    } else {
        plinha linhaAtual = p;
        while (linhaAtual->prox != NULL) {
            linhaAtual = linhaAtual->prox;
        }
        linhaAtual->prox = novaLinha;
    }
    fclose(f);
    return p;
}

//Calcula percursos entre duas paragens
void calculaPercursos(plinha p) {
    if (p == NULL) {
        printf("Nao existem linhas disponiveis!\n");
        return;
    }

    char origem[TAM];
    char destino[TAM];

    printf("\nParagem origem: ");
    scanf(" %[^\n]", origem);
    printf("Paragem destino: ");
    scanf(" %[^\n]", destino);

    plinha linhaAtual = p;
    int flagPercursoEncontrado = 0;

    while (linhaAtual != NULL) {
        int flagOrigem = 0;
        int flagDestino = 0;
        int origemIndice = -1;
        int destinoIndice = -1;

        for (int i = 0; i < linhaAtual->numParagens; i++) {
            if (strcmp(linhaAtual->paragens[i].nomeParagem, origem) == 0) {
                flagOrigem = 1;
                origemIndice = i;
            }
            if (strcmp(linhaAtual->paragens[i].nomeParagem, destino) == 0) {
                flagDestino = 1;
                destinoIndice = i;
            }

            if (flagOrigem && flagDestino) {
                printf("- Linha: %s\n", linhaAtual->nomeLinha);
                printf("  Paragens: ");
                if (origemIndice <= destinoIndice) {
                    for (int j = origemIndice; j <= destinoIndice; j++) {
                        printf("%s ", linhaAtual->paragens[j].nomeParagem);
                    }
                } else {
                    for (int j = origemIndice; j >= destinoIndice; j--) {
                        printf("%s ", linhaAtual->paragens[j].nomeParagem);
                    }
                }
                printf("\n");
                flagPercursoEncontrado = 1;
                break;
            }
        }
        linhaAtual = linhaAtual->prox;
    }
    if (!flagPercursoEncontrado) {
        printf("Nao foram encontrados percursos entre as paragens indicadas.\n");
    }
}


