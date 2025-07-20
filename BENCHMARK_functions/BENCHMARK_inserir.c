#include "../functions/functions_headers.h"

// FUNÇÃO PARA A ANÁLISE DE PERFOMANCE DE INSERÇÃO DAS DUAS ESTRATÉGIAS
void BENCHMARK_inserir (Hash_ES *tabela_ES [], Hash_SL tabela_SL [])
{
    FILE *file;

    #ifdef __WIN32__
        file = fopen ("Execution_Reports\\Insertion_Report.txt", "w");
    #else
        file = fopen ("Execution_Reports/Insertion_Report.txt", "w");
    #endif

    if (!file)
    {
        perror ("");
        exit (EXIT_FAILURE);
    }

    puts ("[INSERÇÃO]\n");
    fprintf (file, "[INSERÇÃO]\n\n");

    int chaves [num_elementos]; // Vetor dos elementos que serão inseridos

    gerar_elementos (num_elementos, chaves);

    clock_t tempo_i;
    double tempo_t = 0.0, tempos [10];
    int colisoes_t = 0;
    
// ========== ENCADEAMENTO SEPARADO ==========

    {
        puts ("Encadeamento separado:");
        fprintf (file, "Encadeamento separado:\n");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {
            iniciar_ES (tabela_ES);

            colisoes_ES = 0;
            tempo_i = clock ();

            for (int j = 0; j < num_elementos; j++)
            {
                inserir_ES (tabela_ES, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;
            
            tempo_t += tempos [i];
            colisoes_t += colisoes_ES;

            liberar_ES (tabela_ES);
        }

        printf ("Para a inserção de %i números inteiros, após 10 execuções diferentes inserindo os mesmos elementos a estratégia de colisão por encadeamento separado resultou em\n\n",
        num_elementos);
        fprintf (file, "Para a inserção de %i números inteiros, após 10 execuções diferentes inserindo os mesmos elementos\na estratégia de colisão por encadeamento separado resultou em\n\n",
        num_elementos);

        printf ("->\tMédia de %i colisões\n->\tTempo médio-aritmético de execução: (%.6lf)s\n",
        colisoes_t / 10, tempo_t / 10.0);
        fprintf (file, "->\tMédia de %i colisões\n->\tTempo médio-aritmético de execução: (%.6lf)s\n\n",
        colisoes_t / 10, tempo_t / 10.0);

        for (int i = 0; i < 10; i++)
        {
            fprintf (file, "[%i]ª execução: (%.6lf)s\n", i + 1, tempos [i]);
        }
    }

    colisoes_t = 0; // Redefinição da medida de colisões total
    tempo_t = 0.0; // Redefinição da medida de tempo total

// ========== SONDAGEM LINEAR ==========

    {
        puts ("\nSondagem linear:");
        fprintf (file, "\nSondagem linear:\n");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {
            iniciar_SL (tabela_SL);
            
            colisoes_SL = 0;
            tempo_i = clock ();

            for (int j = 0; j < num_elementos; j++)
            {
                inserir_SL (tabela_SL, chaves [j]);
            }

            tempos [i] = ((double)(clock () - tempo_i) / CLOCKS_PER_SEC);

            tempo_t += tempos [i];
            colisoes_t += colisoes_SL;
        }

        printf ("Para a inserção de %i números inteiros, após 10 execuções diferentes inserindo os mesmos elementos a estratégia de colisão por sondagem linear resultou em\n\n",
        num_elementos);
        fprintf (file, "Para a inserção de %i números inteiros, após 10 execuções diferentes inserindo os mesmos elementos\na estratégia de colisão por sondagem linear resultou em\n\n",
        num_elementos);

        printf ("->\tMédia de %i colisões\n->\tTempo médio-aritmético de execução: (%.6lf)s\n",
        colisoes_t / 10, tempo_t / 10.0);
        fprintf (file, "->\tMédia de %i colisões\n->\tTempo médio-aritmético de execução: (%.6lf)s\n\n",
        colisoes_t / 10, tempo_t / 10.0);

        for (int i = 0; i < 10; i++)
        {
            fprintf (file, "[%i]ª execução: (%.6lf)s\n", i + 1, tempos [i]);
        }
    }

    fclose (file);
}