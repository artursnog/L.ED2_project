#include "hashing.h"

typedef struct Hash_AB
{
    int chave;
    struct Hash_AB *esq, *dir;
}
Hash_AB;

int colisoes_AB = 0; // CONTADOR DE COLISÕES PARA A FUNÇÃO DE INSERIR

Hash_AB *novo_no (int chave)
{
    Hash_AB *sub_arvore = malloc (sizeof (Hash_AB));

    if (sub_arvore != NULL)
    {
        sub_arvore->chave = chave;
        sub_arvore->dir = NULL;
        sub_arvore->esq = NULL;
    }

    return sub_arvore;
}

void iniciar_AB (Hash_AB *tabela_AB [])
{
    for (int i = 0; i < tamanho; i++)
    {
        tabela_AB [i] = NULL;
    }
}

Hash_AB *inserir_sub_AB (Hash_AB *raiz, int chave) // FUNÇÃO INTERNA DE inserir_AB
{
    if (raiz == NULL)
    {
        return novo_no (chave);
    }

    if (chave < raiz->chave)
    {
        raiz->esq = inserir_sub_AB (raiz->esq, chave);
    }
    else if (chave >= raiz->chave)
    {
        raiz->dir = inserir_sub_AB (raiz->dir, chave);
    }

    return raiz;
}


void inserir_AB (Hash_AB *tabela_AB [], int chave) // FUNÇÃO DE INSERÇÃO
{
    int indice = hashing (chave);

    if (tabela_AB [indice] != NULL)
    {
        colisoes_AB++;
    }

    tabela_AB [indice] = inserir_sub_AB (tabela_AB [indice], chave);
}

Hash_AB *buscar_sub_AB (Hash_AB *raiz, int chave) // FUNÇÃO INTERNA DE buscar_AB
{
    if (raiz == NULL)
    {
        return NULL;
    }

    if (raiz->chave == chave)
    {
        return raiz;
    }
    else if (raiz->chave > chave)
    {
        return buscar_sub_AB (raiz->esq, chave);
    }
    else
    {
        return buscar_sub_AB (raiz->dir, chave);
    }
}

Hash_AB *buscar_AB (Hash_AB *tabela_AB [], int chave) // FUNÇÃO DE BUSCA
{
    int indice = hashing (chave);

    return buscar_sub_AB (tabela_AB [indice], chave);
}

Hash_AB *remover_sub_AB (Hash_AB *raiz, int chave)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    if (chave < raiz->chave)
    {
        raiz->esq = remover_sub_AB (raiz->esq, chave);
    }
    else if (chave > raiz->chave)
    {
        raiz->dir = remover_sub_AB (raiz->dir, chave);
    }
    else
    {
        if ((raiz->esq == NULL) && (raiz->dir == NULL))
        {
            free (raiz);
            return NULL;
        }
        else if (raiz->esq == NULL)
        {
            Hash_AB *tmprr = raiz->dir;

            free (raiz);
            return tmprr;
        }
        else if (raiz->dir == NULL)
        {
            Hash_AB *tmprr = raiz->esq;

            free (raiz);
            return tmprr;
        }
        else
        {
            Hash_AB *tmprr = raiz->dir;

            while (tmprr->esq != NULL)
            {
                tmprr = tmprr->esq;
            }

            raiz->chave = tmprr->chave;

            raiz->dir = remover_sub_AB (raiz->dir, tmprr->chave);
        }
    }

    return raiz;
}

void remover_AB (Hash_AB *tabela_AB [], int chave)
{
    int indice = hashing (chave);

    tabela_AB [indice] = remover_sub_AB (tabela_AB [indice], chave);
}

void liberar_sub_AB (Hash_AB *raiz) // FUNÇÃO INTERNA DE liberar_AB
{
    if (raiz != NULL)
    {
        liberar_sub_AB (raiz->esq);
        liberar_sub_AB (raiz->dir);
        free (raiz);
    }
}

void liberar_AB (Hash_AB *tabela_AB []) // FUNÇÃO PARA LIBERAR A MEMÓRIA DA TABELA INTEIRA
{
    for (int i = 0; i < tamanho; i++)
    {
        liberar_sub_AB (tabela_AB [i]);
        tabela_AB [i] = NULL;
    }
}