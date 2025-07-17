#include "hash.h"

int main ()
{
    srand (time (NULL));

    puts ("\n[Implementação de Tabela Hash com Colisões]");
    puts ("Descrição da atividade: Implemente uma estrutura de tabela hash em C ou C++, com suporte a inserção, busca e remoção.\nTeste duas estratégias de colisão: encadeamento separado e sondagem linear.\nCompare o desempenho de ambas em termos de tempo e número de colisões.\n");
    
    Hash_ES *tabela_ES [tamanho];
    Hash_SL tabela_SL [tamanho];

    BENCHMARK_inserir (tabela_ES, tabela_SL);

    putchar ('\n');
    
    BENCHMARK_buscar (tabela_ES, tabela_SL);

    putchar ('\n');

    return 0;
}