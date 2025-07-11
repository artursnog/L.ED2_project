typedef struct
{
    int chave;
    char status; // 'O' :: OCUPADO, 'R' :: REMOVIDO, 'L' :: LIVRE
}
Hash_SL;

int colisoes_SL = 0; // CONTADOR DE COLISÕES PARA A FUNÇÃO DE INSERIR

int hashing_SL (int chave, int tamanho)
{
    if (chave < 0)
    {
        chave = chave * (-1);
    }

    return chave % tamanho;
}

void iniciar_SL (Hash_SL tabela [], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        tabela [i].status = 'L';
    }
}

void inserir_SL (Hash_SL tabela [], int chave, int tamanho)
{
    int i = 0,
    indice = hashing_SL (chave, tamanho);

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
    }
}

int buscar_SL (Hash_SL tabela [], int chave, int tamanho)
{
    int i = 0,
    indice = hashing_SL (chave, tamanho);

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

void remover_SL (Hash_SL tabela [], int chave, int tamanho)
{
    int indice = buscar_SL (tabela, chave, tamanho);

    if (indice < tamanho)
    {
        tabela [indice].status = 'R';
    }
}