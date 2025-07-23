#include "../functions/functions_headers.h"

// FUNÇÃO PARA A ANÁLISE DE PERFOMANCE DE BUSCA DAS DUAS ESTRATÉGIAS
void BENCHMARK_buscar (Hash_ES *tabela_ES [], Hash_AB *tabela_AB [],  Hash_SL tabela_SL [], Hash_SQ tabela_SQ [], Hash_SD tabela_SD [])
{
    FILE *file;

    #ifdef __WIN32__
        file = fopen ("Execution_Reports\\Searching_Report.txt", "w");
    #else
        file = fopen ("Execution_Reports/Search_Report.txt", "w");
    #endif
    
    if (!file)
    {
        perror ("");
        exit (EXIT_FAILURE);
    }
    
    puts ("[BUSCA]\n");
    fprintf (file, "[BUSCA]\n\n");

    int chaves [num_elementos]; // Vetor dos elementos que serão buscados

    gerar_elementos (num_elementos, chaves);

    clock_t tempo_i;
    double tempo_t = 0.0, tempos [10];

    iniciar_ES (tabela_ES);
    iniciar_SL (tabela_SL);

    for (int i = 0; i < num_elementos; i++) // PREENCHIMENTO DAS TABELAS PARA O TESTE
    {
        inserir_ES (tabela_ES, chaves [i]);
        inserir_SL (tabela_SL, chaves [i]);
        inserir_AB (tabela_AB, chaves [i]);
    }

// ========== ENCADEAMENTO SEPARADO ==========

    {
        puts ("Encadeamento separado:");
        fprintf (file, "Encadeamento separado:n");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {
            tempo_i = clock ();

            for (int j = 0; j < num_elementos; j++)
            {
                buscar_ES (tabela_ES, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;

            tempo_t += tempos [i];
        }

        printf ("Para a busca de %i números inteiros, após 10 execuções diferentes buscando os mesmos elementos a estratégia de tratamento de colisão por encadeamento separado resultou em\n\n",
        num_elementos);
        fprintf (file, "Para a busca de %i números inteiros, após 10 execuções diferentes buscando os mesmos elementos\na estratégia de tratamento de colisão por encadeamento separado resultou em\n\n",
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

// ========== ENCADEAMENTO SEPARADO (COM ÁRVORES BINÁRIAS) ==========

    {
        puts ("\nEncadeamento separado (com árvores binárias):");
        fprintf (file, "\nEncadeamento separado (com árvores binárias):\n");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {
            tempo_i = clock ();

            for (int j = 0; j < num_elementos; j++)
            {
                buscar_AB (tabela_AB, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;

            tempo_t += tempos [i];
        }

        printf ("Para a busca de %i números inteiros, após 10 execuções diferentes buscando os mesmos elementos a estratégia de tratamento de colisão por encadeamento separado com árvores binárias resultou em\n\n",
        num_elementos);
        fprintf (file, "Para a busca de %i números inteiros, após 10 execuções diferentes buscando os mesmos elementos\na estratégia de tratamento de colisão por encadeamento separado com árvores binárias resultou em\n\n",
        num_elementos);

        printf ("->\tTempo médio-aritmético de execução: (%.6lf)s\n",
        tempo_t / 10.0);
        fprintf (file, "->\tTempo médio-aritmético de execução: (%.6lf)s\n\n",
        tempo_t / 10.0);

        for (int i = 0; i < 10; i++)
        {
            fprintf (file, "[%i]ª execução: (%.6lf)s\n", i + 1, tempos [i]);
        }

        liberar_AB (tabela_AB);
    }

    tempo_t = 0.0;

// ========== SONDAGEM LINEAR ==========

    {
        puts ("\nSondagem linear:");
        fprintf (file, "\nSondagem linear:\n");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {
            tempo_i = clock ();

            for (int j = 0; j < num_elementos; j++)
            {
                buscar_SL (tabela_SL, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;

            tempo_t += tempos [i];
        }

        printf ("Para a busca de %i números inteiros, após 10 execuções diferentes buscando os mesmos elementos a estratégia de tratamento de colisão por sondagem linear resultou em\n\n",
        num_elementos);
        fprintf (file, "Para a busca de %i números inteiros, após 10 execuções diferentes buscando os mesmos elementos\na estratégia de colisão por sondagem linear resultou em\n\n",
        num_elementos);

        printf ("->\tTempo médio-aritmético de execução: (%.6lf)s\n",
        tempo_t / 10.0);
        fprintf (file, "->\tTempo médio-aritmético de execução: (%.6lf)s\n\n",
        tempo_t / 10.0);

        for (int i = 0; i < 10; i++)
        {
            fprintf (file, "[%i]ª execução: (%.6lf)s\n", i + 1, tempos [i]);
        }

        liberar_ES (tabela_ES);
    }

    tempo_t = 0.0; 

// ========== SONDAGEM QUADRÁTICA ==========

    {
        puts("\nSondagem quadrática:");
        fprintf(file, "\nSondagem quadrática:\n");

        iniciar_SQ(tabela_SQ);
        for (int j = 0; j < num_elementos; j++)
            inserir_SQ(tabela_SQ, chaves[j]);

        for (int i = 0; i < 10; i++) {
            tempo_i = clock();
            for (int j = 0; j < num_elementos; j++)
                buscar_SQ(tabela_SQ, chaves[j]);
            tempos[i] = (double)(clock() - tempo_i) / CLOCKS_PER_SEC;
            tempo_t += tempos[i];
        }

        printf ("Para a busca de %i números inteiros, após 10 execuções diferentes buscando os mesmos elementos a estratégia de tratamento de colisão por sondagem quadrática resultou em\n\n",
        num_elementos);
        fprintf (file, "Para a busca de %i números inteiros, após 10 execuções diferentes buscando os mesmos elementos\na estratégia de colisão por sondagem quadrática resultou em\n\n",
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

    tempo_t = 0.0;

// ========== HASH DUPLO ==========

    {
        puts("\nHash duplo:");
        fprintf(file, "\nHash duplo:\n");

        iniciar_SD(tabela_SD);
        for (int j = 0; j < num_elementos; j++)
            inserir_SD(tabela_SD, chaves[j]);

        for (int i = 0; i < 10; i++) {
            tempo_i = clock();
            for (int j = 0; j < num_elementos; j++)
                buscar_SD(tabela_SD, chaves[j]);
            tempos[i] = (double)(clock() - tempo_i) / CLOCKS_PER_SEC;
            tempo_t += tempos[i];
        }

        printf ("Para a busca de %i números inteiros, após 10 execuções diferentes buscando os mesmos elementos a estratégia de tratamento de colisão por sondagem dupla (Hash Duplo) resultou em\n\n",
        num_elementos);
        fprintf (file, "Para a busca de %i números inteiros, após 10 execuções diferentes buscando os mesmos elementos\na estratégia de colisão por sondagem dupla (Hash Duplo) resultou em\n\n",
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
    fclose(file);
}
