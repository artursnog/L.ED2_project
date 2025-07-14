#include "dependencies.h"

typedef struct
{
    int chave;
    char status; // 'O' :: OCUPADO, 'R' :: REMOVIDO, 'L' :: LIVRE
}
Hash_SL;

int colisoes_SL = 0; // CONTADOR DE COLISÕES PARA A FUNÇÃO DE INSERIR

void iniciar_SL (Hash_SL tabela [])
{
    for (int i = 0; i < tamanho; i++)
    {
        tabela [i].status = 'L';
    }
}

void inserir_SL (Hash_SL tabela [], int chave)
{
    int i = 0,
    indice = hashing (chave);

    while ((i < tamanho) && (tabela [indice].status == 'O'))
    {
        i = i + 1;
        colisoes_SL = colisoes_SL + 1;
        indice = (indice + 1) % tamanho;
    }

    if (i < tamanho)
    {
        tabela [indice].chave = chave;
        tabela [indice].status = 'O';
    } // SEM NOTIFICAÇÃO DE ELEMENTOS NÃO INSERIDOS DEVIDO A TABELA ESTAR CHEIA
}

int buscar_SL (Hash_SL tabela [], int chave)
{
    int i = 0,
    indice = hashing (chave);

    while ((i < tamanho) && (tabela [indice].chave != chave) && (tabela [indice].status != 'L'))
    {
        i++;
        indice = (indice + 1) % tamanho;
    }

    if ((tabela [indice].chave == chave) && (tabela [indice].status != 'R'))
    {
        return indice;
    }
    else
    {
        return tamanho;
    }
}

void remover_SL (Hash_SL tabela [], int chave)
{
    int indice = buscar_SL (tabela, chave);

    if (indice < tamanho)
    {
        tabela [indice].status = 'R';
    }
}