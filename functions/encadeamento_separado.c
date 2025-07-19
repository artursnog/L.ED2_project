#include "hashing.h"

typedef struct Hash_ES
{
    int chave;
    struct Hash_ES *prox;
}
Hash_ES;

int colisoes_ES = 0; // CONTADOR DE COLISÕES PARA A FUNÇÃO DE INSERIR

void iniciar_ES (Hash_ES *tabela [])
{
    for (int i = 0; i < tamanho; i++)
    {
        tabela [i] = NULL;
    }
}

void inserir_ES (Hash_ES *tabela [], int chave)
{
    int indice = hashing (chave);

    if (tabela [indice] != NULL)
    {
        colisoes_ES = colisoes_ES + 1;
    }

    Hash_ES *novo = (Hash_ES*)malloc (sizeof (Hash_ES));

    if (!novo)
    {
        perror ("");
        exit (EXIT_FAILURE);
    }

    novo->chave = chave;
    novo->prox = tabela [indice];

    tabela [indice] = novo;
}

int buscar_ES (Hash_ES *tabela [], int chave)
{
    Hash_ES *aux = tabela [hashing (chave)];

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

void remover_ES (Hash_ES *tabela [], int chave)
{
    int indice = hashing (chave);
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

void liberar_ES (Hash_ES *tabela [])
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