/*
    Inês Sofia Fernandes Carvalho
    2017015276
    Trabalho Prático - Metro Mondego
*/

#include "paragens.h"
//Visualizar as Paragens
void mostraParagens (paragem *paragens, int total){
    int i;

    //Verificar se tem paragens para mostrar
    if(total==0){
        printf("\nNao existem paragens registadas\n");
        return;
    }
    //Mostrar paragens
    for(i=0;i<total;i++){
        printf("\n\n");
        printf("\nNome da Paragem: %s", paragens[i].nomeParagem);
        printf("\nCodigo da Paragem: %s", paragens[i].codigoParagem);
    }
    printf("\n\n");
}

//Guardar as paragens
void guardarParagens (paragem *paragens, int *total){
    FILE *f;
    int i;

    //1. Abrir o ficheiro
    f=fopen("paragens.dat","wb");
    if(f==NULL){
        printf("\nErro no acesso ao ficheiro paragens!\n");
        return;
    }

    //2. Escrita das paragens no ficheiro
        fwrite(total,sizeof(int),1,f);
        for(i=0;i<*total;i++)
            fwrite(&paragens[i],sizeof(paragem),1,f);

    //3. Fechar ficheiro
    fclose(f);
}

//Carrega as paragens
paragem * carregaParagens (int * total){

    FILE *f;
    int i;
    paragem *a;

    //1. Abrir o ficheiro
    f=fopen("paragens.dat","rb");
    if(f==NULL){
        printf("\nErro no acesso ao ficheiro paragens!\n");
        *total=0;
        return NULL;
    }

    //2. Leitura e escrita das paragens no array dinamico
        fread(total,sizeof(int),1,f);

        a = malloc (sizeof(paragem)* (*total));
        if(a==NULL){
            fclose(f);
            *total=0;
            printf("\nErro ao alocar a memoria!\n");
            return NULL;
        }

        for(i=0;i<*total;i++)
            fread(&a[i],sizeof(paragem),1,f);

    //3. Fechar ficheiro
    fclose(f);
    return a;
}

//Regista uma paragem
paragem * registaParagem(paragem * paragens, int *total){
    paragem *a;

    //Alocar memoria
    a=realloc(paragens, (*total+1) * sizeof(paragem));
    if(a==NULL){
        printf("\nErro ao alocar a memoria!\n");
        return NULL;
    }

    printf("\nNome da Paragem: ");
    scanf(" %[^\n]", a[*total].nomeParagem);
    printf("Codigo da Paragem: ");
    scanf(" %[^\n]", a[*total].codigoParagem);

    //incrementa total
    *total += 1;

    return a;
}

//Elimina uma paragem
void eliminaParagem(paragem *paragens, int *total) {
    int i, encontraParagem = 0;
    char nome[TAM];
    printf("Nome da paragem a eliminar:");
    scanf("%s",nome);

    for (i = 0; i < *total; i++) {
        if (strcmp(nome, paragens[i].nomeParagem) == 0) {
            encontraParagem = 1;
            break;
        }
    }

    if (encontraParagem == 0) {
        printf("\n\nParagem nao encontrada!\n");
    } else {
        // Deslocar os elementos à frente do elemento a ser eliminado
        for (int j = i; j < (*total) - 1; j++) {
            strcpy(paragens[j].nomeParagem, paragens[j + 1].nomeParagem);
            strcpy(paragens[j].codigoParagem, paragens[j + 1].codigoParagem);
        }

        // Redimensionar o array dinâmico
        paragem *tmp = realloc(paragens, (*total - 1) * sizeof(paragem));
        if (tmp == NULL) {
            printf("\nErro ao realocar memória!\n");
            return;
        }

        paragens = tmp;
        (*total)--;
        printf("\n\nParagem eliminada!\n");

    }
}

