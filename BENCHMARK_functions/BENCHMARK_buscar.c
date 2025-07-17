#include "../functions/functions_headers.h"

// FUNÇÃO PARA A ANÁLISE DE PERFOMANCE DE BUSCA DAS DUAS ESTRATÉGIAS
void BENCHMARK_buscar (Hash_ES *tabela_ES [], Hash_SL tabela_SL [])
{
    puts ("[BUSCA]");

    int chaves [num_elementos]; // Vetor dos elementos que serão buscados

    gerar_elementos (num_elementos, chaves);

    clock_t tempo_i;
    double tempo_t = 0.0;

    iniciar_ES (tabela_ES);
    iniciar_SL (tabela_SL);

    for (int i = 0; i < num_elementos; i++)
    {
        inserir_ES (tabela_ES, chaves [i]);
        inserir_SL (tabela_SL, chaves [i]);
    }

// ========== ENCADEAMENTO SEPARADO ==========

    {
        puts ("\nEncadeamento separado:");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {

            tempo_i = clock ();

            for (int j = 0; j < num_elementos; j++)
            {
                buscar_ES (tabela_ES, chaves [j]);
            }

            tempo_t += ((double)(clock () - tempo_i) / CLOCKS_PER_SEC);
        }

        printf ("Para a busca de %i números inteiros, após 10 execuções diferentes buscando os mesmos elementos a estratégia de colisão por encadeamento separado resultou em\n",
        num_elementos);

        printf ("->\tTempo médio-aritmético de execução: (%.6lf)s\n",
        tempo_t / 10.0);
    }

    tempo_t = 0.0; // Redefinição da medida de tempo total

// ========== SONDAGEM LINEAR ==========

    {
        puts ("\nSondagem linear:");

        for (int i = 0; i < 10; i++) // Laço para a tomada de 10 (dez) medida de tempo para a média aritmética
        {
            tempo_i = clock ();

            for (int j = 0; j < num_elementos; j++)
            {
                buscar_SL (tabela_SL, chaves [j]);
            }

            tempo_t += ((double)(clock () - tempo_i) / CLOCKS_PER_SEC);
        }

        printf ("Para a busca de %i números inteiros, após 10 execuções diferentes buscando os mesmos elementos a estratégia de colisão por sondagem linear resultou em\n",
        num_elementos);

        printf ("->\tTempo médio-aritmético de execução: (%.6lf)s\n",
        tempo_t / 10.0);
    }

    liberar_ES (tabela_ES);
}