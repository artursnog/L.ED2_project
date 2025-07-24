#include "../functions/functions_headers.h"

void TMPRR_inicializar (Hash_ES *tabela_ES [], Hash_AB *tabela_AB [], Hash_SL tabela_SL [], Hash_SQ tabela_SQ [], Hash_SD tabela_SD []); // FUNÇÃO LOCAL PARA A INICIALIZAÇÃO E PREENCHIMENTO DAS TABELAS PARA O TESTE

// FUNÇÃO PARA A ANÁLISE DE PERFOMANCE DE BUSCA DAS DUAS ESTRATÉGIAS
void BENCHMARK_buscar ()
{
    FILE *file;

    #ifdef __WIN32__
        file = fopen ("Execution_Reports\\Searching_Report.txt", "w");
    #else
        file = fopen ("Execution_Reports/Search_Report.txt", "w");
    #endif
    
    if (file == NULL)
    {
        perror ("");
        exit (EXIT_FAILURE);
    }

    Hash_ES *tabela_ES [tamanho]; Hash_AB *tabela_AB [tamanho];
    Hash_SL tabela_SL [tamanho]; Hash_SQ tabela_SQ [tamanho]; Hash_SD tabela_SD [tamanho];
    
    gerar_elementos (chaves);
    
    TMPRR_inicializar (tabela_ES, tabela_AB, tabela_SL, tabela_SQ, tabela_SD);

    clock_t tempo_i;
    double tempo_t = 0.0, tempos [10];

    puts ("[BUSCA]\n");
    fprintf (file, "[BUSCA]\n\n");

// ========== ENCADEAMENTO SEPARADO ==========

    {
        puts ("Encadeamento separado:");
        fprintf (file, "=========================\n\nEncadeamento separado:\n");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {
            tempo_i = clock ();

            for (int j = 0; j < NUM_ELEMENTOS; j++)
            {
                buscar_ES (tabela_ES, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;

            tempo_t += tempos [i];
        }

        registrar_dados (file, "encadeamento separado", tempo_t, tempos);

        liberar_ES (tabela_ES);
    }

    tempo_t = 0.0; // Redefinição da medida de tempo total

// ========== ENCADEAMENTO SEPARADO (COM ÁRVORES BINÁRIAS) ==========

    {
        puts ("\nEncadeamento separado (com árvores binárias):");
        fprintf (file, "\n=========================\n\nEncadeamento separado (com árvores binárias):\n");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {
            tempo_i = clock ();

            for (int j = 0; j < NUM_ELEMENTOS; j++)
            {
                buscar_AB (tabela_AB, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;

            tempo_t += tempos [i];
        }

        registrar_dados (file, "encadeamento separado com árvores binárias", tempo_t, tempos);

        liberar_AB (tabela_AB);
    }

    tempo_t = 0.0;

// ========== SONDAGEM LINEAR ==========

    {
        puts ("\nSondagem linear:");
        fprintf (file, "\n=========================\n\nSondagem linear:\n");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {
            tempo_i = clock ();

            for (int j = 0; j < NUM_ELEMENTOS; j++)
            {
                buscar_SL (tabela_SL, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;

            tempo_t += tempos [i];
        }

        registrar_dados (file, "sondagem linear", tempo_t, tempos);
    }

    tempo_t = 0.0; 

// ========== SONDAGEM QUADRÁTICA ==========

    {
        puts("\nSondagem quadrática:");
        fprintf(file, "\n=========================\n\nSondagem quadrática:\n");

        iniciar_SQ(tabela_SQ);
        for (int j = 0; j < NUM_ELEMENTOS; j++)
            inserir_SQ(tabela_SQ, chaves[j]);

        for (int i = 0; i < 10; i++) {
            tempo_i = clock();
            for (int j = 0; j < NUM_ELEMENTOS; j++)
                buscar_SQ(tabela_SQ, chaves[j]);
            tempos[i] = (double)(clock() - tempo_i) / CLOCKS_PER_SEC;
            tempo_t += tempos[i];
        }

        registrar_dados (file, "sondagem quadrática", tempo_t, tempos);
    }

    tempo_t = 0.0;

// ========== HASH DUPLO ==========

    {
        puts("\nHash duplo:");
        fprintf(file, "\n=========================\n\nHash duplo:\n");

        iniciar_SD(tabela_SD);
        for (int j = 0; j < NUM_ELEMENTOS; j++)
            inserir_SD(tabela_SD, chaves[j]);

        for (int i = 0; i < 10; i++) {
            tempo_i = clock();
            for (int j = 0; j < NUM_ELEMENTOS; j++)
                buscar_SD(tabela_SD, chaves[j]);
            tempos[i] = (double)(clock() - tempo_i) / CLOCKS_PER_SEC;
            tempo_t += tempos[i];
        }

        registrar_dados (file, "hash duplo", tempo_t, tempos);

    }
    BREAKL;

    fclose(file);
}

void TMPRR_inicializar (Hash_ES *tabela_ES [], Hash_AB *tabela_AB [], Hash_SL tabela_SL [], Hash_SQ tabela_SQ [], Hash_SD tabela_SD [])
{
    iniciar_ES (tabela_ES);
    iniciar_AB (tabela_AB);
    iniciar_SL (tabela_SL);
    iniciar_SQ (tabela_SQ);
    iniciar_SD (tabela_SD);

    for (int i = 0; i < NUM_ELEMENTOS; i++)
    {
        inserir_ES (tabela_ES, chaves [i]);
        inserir_AB (tabela_AB, chaves [i]);
        inserir_SL (tabela_SL, chaves [i]);
        inserir_SQ (tabela_SQ, chaves [i]);
        inserir_SD (tabela_SD, chaves [i]);
    }
}