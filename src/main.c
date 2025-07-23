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

    puts ("\n[Implementação de Tabela Hash com Colisões]");
    puts ("Descrição da atividade: Implemente uma estrutura de tabela hash em C ou C++, com suporte a inserção, busca e remoção.\nTeste duas estratégias de colisão: encadeamento separado e sondagem linear.\nCompare o desempenho de ambas em termos de tempo e número de colisões.");
    
    BREAKL;

    BENCHMARK_inserir ();
    BENCHMARK_buscar ();
    BENCHMARK_remover ();

    return 0;
}