#include "../functions/functions_headers.h"

void TMPRR_inserir_ES (Hash_ES *tabela_ES [], int chaves []) // FUNÇÃO LOCAL PARA A INSERÇÃO NA TABELA DE ENCADEAMENTO SEPARADO APÓS ESVAZIAMENTO POR TESTE
{
    iniciar_ES (tabela_ES);

    for (int i = 0; i < num_elementos; i++)
    {
        inserir_ES (tabela_ES, chaves [i]);
    }
}

void TMPRR_inserir_SL (Hash_SL tabela_SL [], int chaves []) // FUNÇÃO LOCAL PARA A INSERÇÃO NA TABELA DE SONDAGEM LINEAR APÓS ESVAZIAMENTO POR TESTE
{
    iniciar_SL (tabela_SL);

    for (int i = 0; i < num_elementos; i++)
    {
        inserir_SL (tabela_SL, chaves [i]);
    }
}

// FUNÇÃO PARA A ANÁLISE DE PERFOMANCE DE REMOÇÃO DAS DUAS ESTRATÉGIAS
void BENCHMARK_remover (Hash_ES *tabela_ES [], Hash_SL tabela_SL [])
{
    FILE *file = fopen ("Relatórios de execução/Relatório_Remoção.txt", "w");
    if (!file)
    {
        perror ("");
        exit (EXIT_FAILURE);
    }

    puts ("[REMOÇÃO]\n");
    fprintf (file, "[REMOÇÃO]\n\n");

    int chaves [num_elementos]; // Vetor dos elementos que serão inseridos

    gerar_elementos (num_elementos, chaves);

    clock_t tempo_i;
    double tempo_t = 0.0, tempos [10];

// ========== ENCADEAMENTO SEPARADO ==========

    {
        puts ("Encadeamento separado:");
        fprintf (file, "Encadeamento separado:\n");

        for (int i = 0; i < 10; i++)
        {
            TMPRR_inserir_ES (tabela_ES, chaves);

            tempo_i = clock ();

            for (int j = 0; j < num_elementos; j++)
            {
                remover_ES (tabela_ES, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;

            tempo_t += tempos [i];

            liberar_ES (tabela_ES); // LIBERAR ANTES DA REINSERÇÃO DOS ELEMENTOS PARA NOVO TESTE
        }

        printf ("Para a remoção de %i números inteiros, após 10 execuções diferentes removendo os mesmos elementos a estratégia de colisão por encadeamento separado resultou em\n\n",
        num_elementos);
        fprintf (file, "Para a remoção de %i números inteiros, após 10 execuções diferentes removendo os mesmos elementos\na estratégia de colisão por encadeamento separado resultou em\n\n",
        num_elementos);

        printf ("->\tTempo médio-aritmético de execução: (%.6lf)s\n",
        tempo_t / 10.0);
        fprintf (file, "->\tTempo médio-aritmético de execução: (%.6lf)s\n\n",
        tempo_t / 10.0);

        for (int i = 0; i < 10; i++)
        {
            fprintf (file, "[%i]ª execução: (%.6lf)s\n", i + 1, tempos [i]);
        }
    }

    tempo_t = 0.0; // Redefinição da medida de tempo total

// ========== SONDAGEM LINEAR ==========

    {
        puts ("\nSondagem linear:");
        fprintf (file, "\nSondagem linear:\n");

        for (int i = 0; i < 10; i++)
        {
            TMPRR_inserir_SL (tabela_SL, chaves);

            tempo_i = clock ();

            for (int j = 0; j < num_elementos; j++)
            {
                remover_SL (tabela_SL, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;

            tempo_t += tempos [i];
        }

        printf ("Para a remoção de %i números inteiros, após 10 execuções diferentes removendo os mesmos elementos a estratégia de colisão por sondagem linear resultou em\n\n",
        num_elementos);
        fprintf (file, "Para a remoção de %i números inteiros, após 10 execuções diferentes removendo os mesmos elementos\na estratégia de colisão por sondagem linear resultou em\n\n",
        num_elementos);

        printf ("->\tTempo médio-aritmético de execução: (%.6lf)s\n",
        tempo_t / 10.0);
        fprintf (file, "->\tTempo médio-aritmético de execução: (%.6lf)s\n\n",
        tempo_t / 10.0);

        for (int i = 0; i < 10; i++)
        {
            fprintf (file, "[%i]ª execução: (%.6lf)s\n", i + 1, tempos [i]);
        }
    }

    fclose (file);
}