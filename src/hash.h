#include "../functions/encadeamento_separado.c"
#include "../functions/sondagem_linear.c"

// FUNÇÃO PARA A ANÁLISE DE PERFOMANCE DE INSERÇÃO DAS DUAS ESTRATÉGIAS
void inserir_TESTBANK (Hash_ES *tabela_ES [], Hash_SL tabela_SL [], int chaves [], int num_elementos)
{
    puts ("[INSERÇÃO]");

    clock_t tempo_i;
    double tempo_t;
    
    {
        puts ("Encadeamento separado:");

        tempo_i = clock ();

        for (int i = 0; i < num_elementos; i++)
        {
            inserir_ES (tabela_ES, chaves [i]);
        }

        tempo_t = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;

        printf ("Para a inserção de %i números inteiros, a estratégia de colisão por encadeamento separado resultou em\n", num_elementos);
        printf ("->\t%i colisões\n->\tTempo de execução: (%lf)s\n", colisoes_ES, tempo_t);
    }

    {
        puts ("\nSondagem linear:");

        tempo_i = clock ();

        for (int i = 0; i < num_elementos; i++)
        {
            inserir_SL (tabela_SL, chaves [i]);
        }

        tempo_t = (double)(clock () - tempo_i) / CLOCKS_PER_SEC;

        printf ("Para a inserção de %i números inteiros, a estratégia de colisão por sondagem linear resultou em\n", num_elementos);
        printf ("->\t%i colisões\n->\tTempo de execução: (%lf)s\n", colisoes_SL, tempo_t);
    }
}