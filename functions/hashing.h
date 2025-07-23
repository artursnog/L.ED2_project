#ifndef HASHING_H
#define HASHING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BREAKL puts ("\n==================================================\n")
#define NUM_ELEMENTOS 1009

const int tamanho = 997;

int chaves [NUM_ELEMENTOS];

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

int hashing2(int chave){
    return 1 + (chave % (tamanho));
}

void gerar_elementos (int chaves [])
{
    for (int i = 0; i < NUM_ELEMENTOS; i++)
    {
        chaves [i] = rand ();
    }
}

void registrar_dados_inserir (FILE *file, char String [], int colisoes_t, double tempo_t, double tempos [])
{
    printf ("Para a inserção de %i números inteiros, após 10 execuções diferentes inserindo os mesmos elementos a estratégia de tratamento de colisão por %s resultou em\n\n",
    NUM_ELEMENTOS, String);
    fprintf (file, "Para a inserção de %i números inteiros, após 10 execuções diferentes inserindo os mesmos elementos\na estratégia de tratamento de colisão por %s resultou em\n\n",
    NUM_ELEMENTOS, String);

    printf ("->\tMédia de %i colisões\n->\tTempo médio-aritmético de execução: (%.6lf)s\n",
    colisoes_t / 10, tempo_t / 10.0);
    fprintf (file, "->\tMédia de %i colisões\n->\tTempo médio-aritmético de execução: (%.6lf)s\n\n",
    colisoes_t / 10, tempo_t / 10.0);

    for (int i = 0; i < 10; i++)
    {
        fprintf (file, "[%i]ª execução: (%.6lf)s\n", i + 1, tempos [i]);
    }
}

void registrar_dados (FILE *file, char String [], double tempo_t, double tempos [])
{
    printf ("Para a inserção de %i números inteiros, após 10 execuções diferentes inserindo os mesmos elementos a estratégia de tratamento de colisão por %s resultou em\n\n",
    NUM_ELEMENTOS, String);
    fprintf (file, "Para a inserção de %i números inteiros, após 10 execuções diferentes inserindo os mesmos elementos\na estratégia de tratamento de colisão por %s resultou em\n\n",
    NUM_ELEMENTOS, String);

    printf ("->\tTempo médio-aritmético de execução: (%.6lf)s\n",
    tempo_t / 10.0);
    fprintf (file, "->\tTempo médio-aritmético de execução: (%.6lf)s\n\n",
    tempo_t / 10.0);

    for (int i = 0; i < 10; i++)
    {
        fprintf (file, "[%i]ª execução: (%.6lf)s\n", i + 1, tempos [i]);
    }
}

#endif