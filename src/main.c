/*
Implemente uma estrutura de tabela hash em C ou C++, com suporte a
inserção, busca e remoção. Teste duas estratégias de colisão: encadeamento separado e sondagem linear.
Compare o desempenho de ambas em termos de tempo e número de colisões.
*/

#include "hash.h"

int main ()
{
    srand (time (NULL));

    puts ("\n[Implementação de Tabela Hash com Colisões]");
    puts ("Descrição da atividade: Implemente uma estrutura de tabela hash em C ou C++, com suporte a inserção, busca e remoção.\nTeste duas estratégias de colisão: encadeamento separado e sondagem linear.\nCompare o desempenho de ambas em termos de tempo e número de colisões.\n");
    
    int chaves [num_elementos];
    double tempo_t;
    
    for (int i = 0; i < num_elementos; i++)
    {
        chaves [i] = rand ();
    }

    Hash_ES *tabela_ES [tamanho];
    iniciar_ES (tabela_ES);

    Hash_SL tabela_SL [tamanho];
    iniciar_SL (tabela_SL);

    inserir_TESTBANK (tabela_ES, tabela_SL, chaves, num_elementos);

    putchar ('\n');

    liberar_ES (tabela_ES);

    return 0;
}