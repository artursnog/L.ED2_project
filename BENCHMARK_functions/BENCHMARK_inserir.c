#include "../functions/functions_headers.h"

// FUNÇÃO PARA A ANÁLISE DE PERFOMANCE DE INSERÇÃO DAS DUAS ESTRATÉGIAS
void BENCHMARK_inserir ()
{
    FILE *file;

    #ifdef __WIN32__
        file = fopen ("Execution_Reports\\Insertion_Report.txt", "w");
    #else
        file = fopen ("Execution_Reports/Insertion_Report.txt", "w");
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
    int colisoes_t = 0;

    puts ("[INSERÇÃO]\n");
    fprintf (file, "[INSERÇÃO]\n\n");
    
// ========== ENCADEAMENTO SEPARADO ==========

    {
        puts ("Encadeamento separado:");
        fprintf (file, "=========================\n\nEncadeamento separado:\n");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {
            iniciar_ES (tabela_ES);

            colisoes_ES = 0;
            tempo_i = clock ();

            for (int j = 0; j < NUM_ELEMENTOS; j++)
            {
                inserir_ES (tabela_ES, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;
            tempo_t += tempos [i];
            colisoes_t += colisoes_ES;

            liberar_ES (tabela_ES);
        }

        registrar_dados_inserir (file, "encadeamento separado", colisoes_t, tempo_t, tempos);
    }

    colisoes_t = 0; // Redefinição da medida de colisões total
    tempo_t = 0.0; // Redefinição da medida de tempo total

// ========== ENCADEAMENTO SEPARADO (COM ÁRVORES BINÁRIAS DE BUSCA) ==========

    {
        puts ("\nEncadeamento separado com árvores binárias de busca:");
        fprintf (file, "\n=========================\n\nEncadeamento separado (com árvores binárias de busca):\n");

        for (int i = 0; i < 10; i++)
        {
            iniciar_AB (tabela_AB);

            colisoes_AB = 0;
            tempo_i = clock ();

            for (int j = 0; j < NUM_ELEMENTOS; j++)
            {
                inserir_AB (tabela_AB, chaves [j]);
            }

            tempos [i] = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;
            tempo_t += tempos [i];
            colisoes_t += colisoes_AB;

            liberar_AB (tabela_AB);
        }

        registrar_dados_inserir (file, "encadeamento separado com árvores binárias de busca", colisoes_t, tempo_t, tempos);
    }

    colisoes_t = 0;
    tempo_t = 0.0;

// ========== SONDAGEM LINEAR ==========

    {
        puts ("\nSondagem linear:");
        fprintf (file, "\n=========================\n\nSondagem linear:\n");

        for (int i = 0; i < 10; i++)
        {
            iniciar_SL (tabela_SL);
            
            colisoes_SL = 0;
            tempo_i = clock ();

            for (int j = 0; j < NUM_ELEMENTOS; j++)
            {
                inserir_SL (tabela_SL, chaves [j]);
            }

            tempos [i] = ((double)(clock () - tempo_i) / CLOCKS_PER_SEC);
            tempo_t += tempos [i];
            colisoes_t += colisoes_SL;
        }

        registrar_dados_inserir (file, "sondagem linear", colisoes_t, tempo_t, tempos);
    }

    colisoes_t = 0; 
    tempo_t = 0.0; 

// ========== SONDAGEM QUADRÁTICA ==========

    {
        puts ("\nSondagem quadrática:");
        fprintf (file, "\n=========================\n\nSondagem quadrática:\n");

        for (int i = 0; i < 10; i++)
        {
            iniciar_SQ(tabela_SQ);
            
            colisoes_SQ = 0;
            tempo_i = clock ();

            for (int j = 0; j < NUM_ELEMENTOS; j++)
            {
                inserir_SQ(tabela_SQ, chaves[j]);
            }

            tempos[i] = ((double)(clock () - tempo_i) / CLOCKS_PER_SEC);
            tempo_t += tempos[i];
            colisoes_t += colisoes_SQ;
        }

        registrar_dados_inserir (file, "sondagem quadrática", colisoes_t, tempo_t, tempos);
    }

    colisoes_t = 0;
    tempo_t = 0.0;

// ========== DUPLO HASHING ==========

    {
        puts ("\nHash duplo:");
        fprintf (file, "\n=========================\n\nHash duplo:\n");

        for (int i = 0; i < 10; i++)
        {
            iniciar_SD(tabela_SD);
            
            colisoes_SD = 0;
            tempo_i = clock ();

            for (int j = 0; j < NUM_ELEMENTOS; j++)
            {
                inserir_SD(tabela_SD, chaves[j]);
            }

            tempos[i] = ((double)(clock () - tempo_i) / CLOCKS_PER_SEC);
            tempo_t += tempos[i];
            colisoes_t += colisoes_SD;
        }

        registrar_dados_inserir (file, "hash duplo", colisoes_t, tempo_t, tempos);
    }

    BREAKL;

    fclose (file);
}