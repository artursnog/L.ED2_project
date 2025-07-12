#include <stdlib.h>

typedef struct Hash_ES
{
    int chave;
    struct Hash_ES *prox;
}
Hash_ES;

int hashing_ES (int chave, int tamanho)
{
    if (chave < 0)
    {
        chave = chave * (-1);
    }

    return chave % tamanho;
}

void inserir_ES (Hash_ES *tabela [], int chave, int tamanho)
{
    Hash_ES *novo = (Hash_ES*)malloc (sizeof (Hash_ES));

    novo->chave = chave;
    novo->prox = tabela [hashing_ES (chave, tamanho)];

    tabela [hashing_ES (chave, tamanho)] = novo;
}

int buscar_ES (Hash_ES *tabela [], int chave, int tamanho)
{
    Hash_ES *aux = tabela [hashing_ES (chave, tamanho)];

    while (aux != NULL)
    {
        if (aux->chave == chave)
        {
            return aux->chave;
        }

        aux = aux->prox;
    }

    return -1;
}

void excluir_ES (Hash_ES *tabela [], int chave, int tamanho)
{
    int indice = hashing_ES (chave, tamanho);
    Hash_ES *aux;

    if (tabela [indice] != NULL)
    {
        if (tabela [indice]->chave == chave)
        {
            aux = tabela [indice];
            tabela [indice] = tabela [indice]->prox;
            free (aux);
        }
        else
        {
            aux = tabela [indice]->prox;
            Hash_ES *ant = tabela [indice];

            while ((aux != NULL) && (aux->chave != chave))
            {
                ant = aux;
                aux = aux->prox;
            }

            if (aux != NULL)
            {
                ant->prox = aux->prox;
                free (aux);
            }
        }
    }
}

void liberar_ES (Hash_ES *tabela [], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        Hash_ES *aux = tabela [i];

        while (aux != NULL)
        {
            Hash_ES *tmprr = aux;
            aux = aux->prox;
            free (tmprr);
        }
        tabela [i] = NULL;
    }
}