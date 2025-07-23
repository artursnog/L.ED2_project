#include "hashing.h"

typedef struct{
    int chave;
    char status;
} Hash_SD;

int colisoes_SD = 0;

void iniciar_SD(Hash_SD tabela[]){
    for(int i = 0; i < tamanho; i++){
        tabela[i].status = 'L';
    }
}

void inserir_SD(Hash_SD tabela[], int chave){
    int indice = hashing(chave), indice2 = hashing2(chave), i = 0;

    while((i < tamanho) && (tabela[indice]. status == 'O')){
        colisoes_SD++;
        i++;
        indice = (indice+i*indice2) % tamanho;
    }
    if(i  < tamanho){
        tabela[indice].chave = chave;
        tabela[indice].status = 'O';
    }
}

int buscar_SD(Hash_SD tabela[], int chave){
    int indice = hashing(chave), indice2 = hashing2(chave), i = 0;

    while((i < tamanho) && (tabela[indice].status != 'L') && (tabela[indice].chave != chave)){
        i++;
        indice = (indice+i*indice2) % tamanho;
    }
    if((tabela[indice].status == 'O') && (tabela[indice].chave == chave)){
        return indice;
    }
    return tamanho;
}

void remover_SD(Hash_SD tabela[], int chave){
    int indice = buscar_SD(tabela, chave);
    
    if(indice < tamanho){
        tabela[indice].status = 'R';
    }
}