#include "hash.h"

#ifdef __WIN32__
    #include <locale.h>
#endif

int main ()
{
    #ifdef __WIN32__
        setlocale (LC_ALL, "Portuguese");
    #endif
    
    srand (time (NULL));

    Hash_ES *tabela_ES [tamanho];
    Hash_AB *tabela_AB [tamanho];
    Hash_SL tabela_SL [tamanho];
    Hash_SQ tabela_SQ [tamanho];
    Hash_SD tabela_SD [tamanho];

    puts ("\n[Implementação de Tabela Hash com Colisões]");
    puts ("Descrição da atividade: Implemente uma estrutura de tabela hash em C ou C++, com suporte a inserção, busca e remoção.\nTeste duas estratégias de colisão: encadeamento separado e sondagem linear.\nCompare o desempenho de ambas em termos de tempo e número de colisões.");
    
    BREAKL;

    BENCHMARK_inserir (tabela_ES, tabela_AB, tabela_SL, tabela_SQ, tabela_SD);

    BREAKL;
    
    BENCHMARK_buscar (tabela_ES, tabela_AB, tabela_SL, tabela_SQ, tabela_SD);

    BREAKL;

    BENCHMARK_remover (tabela_ES, tabela_AB, tabela_SL, tabela_SQ, tabela_SD);

    putchar ('\n');

    return 0;
}