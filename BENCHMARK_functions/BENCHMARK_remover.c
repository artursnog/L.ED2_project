#include "../functions/functions_headers.h"

void TMPRR_inserir_ES (Hash_ES *tabela_ES [], int chaves []);
void TMPRR_inserir_AB (Hash_AB *tabela_AB [], int chaves []);
void TMPRR_inserir_SL (Hash_SL tabela_SL [], int chaves []);
void TMPRR_inserir_SQ (Hash_SQ tabela_SQ [], int chaves []);
void TMPRR_inserir_SD (Hash_SD tabela_SD [], int chaves []);

// FUNÇÃO PARA A ANÁLISE DE PERFOMANCE DE REMOÇÃO DAS DUAS ESTRATÉGIAS
void BENCHMARK_remover ()
{
    FILE *file;

    #ifdef __WIN32__
        file = fopen ("Execution_Reports\\Removal_Report.txt", "w");
    #else
        file = fopen ("Execution_Reports/Removal_Report.txt", "w");
    #endif
    
    if (file == NULL)
    {
        perror ("");
        exit (EXIT_FAILURE);
    }

    Hash_ES *tabela_ES [tamanho]; Hash_AB *tabela_AB [tamanho];
    Hash_SL tabela_SL [tamanho]; Hash_SQ tabela_SQ [tamanho]; Hash_SD tabela_SD [tamanho];
    
    gerar_elementos (chaves);
    
    clock_t tempo_i;
    double tempo_t = 0.0, tempos [10];

    puts ("[REMOÇÃO]\n");
    fprintf (file, "[REMOÇÃO]\n\n");

// ========== ENCADEAMENTO SEPARADO ==========

    {
        puts ("Encadeamento separado:");
        fprintf (file, "=========================\n\nEncadeamento separado:\n");

        for (int i = 0; i < 10; i++)
        {
            TMPRR_inserir_ES (tabela_ES, chaves);

            tempo_i = clock ();

            for (int j = 0; j < NUM_ELEMENTOS; j++)
            {
                remover_ES (tabela_ES, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;

            tempo_t += tempos [i];

            liberar_ES (tabela_ES); // LIBERAR ANTES DA REINSERÇÃO DOS ELEMENTOS PARA NOVO TESTE
        }

        registrar_dados (file, "encadeamento separado", tempo_t, tempos);
    }

    tempo_t = 0.0; // Redefinição da medida de tempo total

// ========== ENCADEAMENTO SEPARADO (COM ÁRVORES BINÁRIAS) ==========

    {
        puts ("\nEncadeamento separado com árvores binárias:");
        fprintf (file, "\n=========================\n\nEncadeamento separado com árvores binárias:\n");

        for (int i = 0; i < 10; i++)
        {
            TMPRR_inserir_AB (tabela_AB, chaves);

            tempo_i = clock ();

            for (int j = 0; j < NUM_ELEMENTOS; j++)
            {
                remover_AB (tabela_AB, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;

            tempo_t += tempos [i];

            liberar_AB (tabela_AB); // LIBERAR ANTES DA REINSERÇÃO DOS ELEMENTOS PARA NOVO TESTE
        }

        registrar_dados (file, "encadeamento separado com árvores binárias", tempo_t, tempos);
    }

    tempo_t = 0.0;

// ========== SONDAGEM LINEAR ==========

    {
        puts ("\nSondagem linear:");
        fprintf (file, "\n=========================\n\nSondagem linear:\n");

        for (int i = 0; i < 10; i++)
        {
            TMPRR_inserir_SL (tabela_SL, chaves);

            tempo_i = clock ();

            for (int j = 0; j < NUM_ELEMENTOS; j++)
            {
                remover_SL (tabela_SL, chaves [j]);
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

        for (int i = 0; i < 10; i++) {
            iniciar_SQ(tabela_SQ);
            for (int j = 0; j < NUM_ELEMENTOS; j++)
                inserir_SQ(tabela_SQ, chaves[j]);

            tempo_i = clock();
            for (int j = 0; j < NUM_ELEMENTOS; j++)
                remover_SQ(tabela_SQ, chaves[j]);
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

        for (int i = 0; i < 10; i++) {
            iniciar_SD(tabela_SD);
            for (int j = 0; j < NUM_ELEMENTOS; j++)
                inserir_SD(tabela_SD, chaves[j]);

            tempo_i = clock();
            for (int j = 0; j < NUM_ELEMENTOS; j++)
                remover_SD(tabela_SD, chaves[j]);
            tempos[i] = (double)(clock() - tempo_i) / CLOCKS_PER_SEC;
            tempo_t += tempos[i];
        }

        registrar_dados (file, "hash duplo", tempo_t, tempos);

    }

    BREAKL;

    fclose (file);
}

void TMPRR_inserir_ES (Hash_ES *tabela_ES [], int chaves []) // FUNÇÃO LOCAL PARA A INSERÇÃO NA TABELA DE ENCADEAMENTO SEPARADO APÓS ESVAZIAMENTO POR TESTE
{
    iniciar_ES (tabela_ES);

    for (int i = 0; i < tamanho; i++)
    {
        inserir_ES (tabela_ES, chaves [i]);
    }
}

void TMPRR_inserir_AB (Hash_AB *tabela_AB [], int chaves []) // FUNÇÃO LOCAL PARA A INSERÇÃO NA TABELA DE ENCADEAMENTO COM ÁRVORES BINÁRIAS
{
    iniciar_AB (tabela_AB);

    for (int i = 0; i < tamanho; i++)
    {
        inserir_AB (tabela_AB, chaves [i]);
    }
}

void TMPRR_inserir_SL (Hash_SL tabela_SL [], int chaves []) // FUNÇÃO LOCAL PARA A INSERÇÃO NA TABELA DE SONDAGEM LINEAR APÓS ESVAZIAMENTO POR TESTE
{
    iniciar_SL (tabela_SL);

    for (int i = 0; i < tamanho; i++)
    {
        inserir_SL (tabela_SL, chaves [i]);
    }
}

void TMPRR_inserir_SQ (Hash_SQ tabela_SQ [], int chaves []){ // FUNÇÃO LOCAL PARA A INSERÇÃO NA TABELA DE SONDAGEM QUADRADICA APÓS ESVAZIAMENTO POR TESTE
    iniciar_SQ (tabela_SQ);

    for(int i = 0; i < tamanho; i++){
        inserir_SQ (tabela_SQ, chaves [i]);
    }
}

void TMPRR_inserir_SD (Hash_SD tabela_SD [], int chaves []){ // FUNÇÃO LOCAL PARA A INSERÇÃO NA TABELA DE SONDAGEM DUPLA (HASH DUPLO) APÓS ESVAZIAMENTO POR TESTE
    iniciar_SD (tabela_SD);
    
    for(int i = 0; i < tamanho; i++){
        inserir_SD (tabela_SD, chaves [i]);
    }
}