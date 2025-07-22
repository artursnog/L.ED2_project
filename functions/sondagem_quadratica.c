#include "hashing.h"

typedef struct{
    int chave;
    char status;
} Hash_SQ;

int colisoes_SQ = 0;

void iniciar_SQ(Hash_SQ tabela[]){
    for(int i = 0; i < tamanho; i++){
        tabela[i].status = 'L';
    }
}

void inserir_SQ(Hash_SQ tabela[], int chave){
    int indice = hashing(chave), i = 0;

    while((i < tamanho) && (tabela[indice].status == 'O')){
        colisoes_SQ++;
        i++;
        indice = (indice + i*i) % tamanho;
    }

    if (i < tamanho){
        tabela[indice].chave = chave;
        tabela[indice].status = 'O';
    }
}

int buscar_SQ(Hash_SQ tabela[], int chave){
    int indice = hashing(chave), i = 0;

    while((i < tamanho) && (tabela[indice].status != 'L') && (tabela[indice].chave != chave)){
        i++;
        indice = (indice + i*i) % tamanho;
    }

    if((tabela[indice].status == 'O') && (tabela[indice].chave == chave)){
        return indice;
    }
    return tamanho;
}

void remover_SQ(Hash_SQ tabela[], int chave){
    int indice = buscar_SQ(tabela, chave);

    if(indice < tamanho){
        tabela[indice].status = 'R';
    }
}