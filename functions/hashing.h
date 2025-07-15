#ifndef HASHING_H
#define HASHING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int tamanho = 997,
num_elementos = 1009;

int hashing (int chave)
{
    if (chave < 0)
    {
        chave = chave * (-1);
    }

    double GR = 0.61803398875,
    k_A_mod1 = ((chave * GR) - (int)(chave * GR));

    return (int)(tamanho * k_A_mod1);
}

#endif