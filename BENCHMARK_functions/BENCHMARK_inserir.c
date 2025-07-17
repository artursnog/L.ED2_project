#include "../functions/functions_headers.h"

// FUNÇÃO PARA A ANÁLISE DE PERFOMANCE DE INSERÇÃO DAS DUAS ESTRATÉGIAS
void BENCHMARK_inserir (Hash_ES *tabela_ES [], Hash_SL tabela_SL [])
{
    puts ("[INSERÇÃO]");

    int chaves [num_elementos]; // Vetor dos elementos que serão inseridos

    gerar_elementos (num_elementos, chaves);

    clock_t tempo_i;
    double tempo_t = 0.0;
    int colisoes_t = 0;
    
// ========== ENCADEAMENTO SEPARADO ==========

    {
        puts ("Encadeamento separado:");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {
            iniciar_ES (tabela_ES);

            colisoes_ES = 0;
            tempo_i = clock ();

            for (int j = 0; j < num_elementos; j++)
            {
                inserir_ES (tabela_ES, chaves [j]);
            }
            
            tempo_t += ((double)(clock () - tempo_i) / CLOCKS_PER_SEC);
            colisoes_t += colisoes_ES;

            liberar_ES (tabela_ES);
        }

        printf ("Para a inserção de %i números inteiros, após 10 execuções diferentes inserindo os mesmos elementos a estratégia de colisão por encadeamento separado resultou em\n",
        num_elementos);

        printf ("->\tMédia de %i colisões\n->\tTempo médio-aritmético de execução: (%.6lf)s\n",
        colisoes_t / 10, tempo_t / 10.0);
    }

    colisoes_t = 0; // Redefinição da medida de colisões total
    tempo_t = 0.0; // Redefinição da medida de tempo total

// ========== SONDAGEM LINEAR ==========

    {
        puts ("\nSondagem linear:");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {
            iniciar_SL (tabela_SL);
            
            colisoes_SL = 0;
            tempo_i = clock ();

            for (int j = 0; j < num_elementos; j++)
            {
                inserir_SL (tabela_SL, chaves [j]);
            }

            tempo_t += ((double)(clock () - tempo_i) / CLOCKS_PER_SEC);
            colisoes_t += colisoes_SL;
        }

        printf ("Para a inserção de %i números inteiros, após 10 execuções diferentes inserindo os mesmos elementos a estratégia de colisão por sondagem linear resultou em\n",
        num_elementos);

        printf ("->\tMédia de %i colisões\n->\tTempo médio-aritmético de execução: (%.6lf)s\n",
        colisoes_t / 10, tempo_t / 10.0);
    }
}