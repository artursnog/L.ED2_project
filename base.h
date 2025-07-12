#include <stdio.h>
#include <stdlib.h>

const int tamanho = 31415;

int hashing (int chave)
{
    if (chave < 0)
    {
        chave = chave * (-1);
    }

    return chave % tamanho;
}