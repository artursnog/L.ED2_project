<img title="ufersa" alt="logoufersa" src="https://assecom.ufersa.edu.br/wp-content/uploads/sites/24/2014/09/PNG-bras%C3%A3o-Ufersa.png" width="100">

# Trabalho Avaliativo Final Estruturas de Dados 2

## Universidade Federal Rural do Semi-Árido - UFERSA
### Implementação de Tabela Hash com Colisões

## Descrição do Projeto

Este projeto implementa uma estrutura de tabela hash em linguagem C, comparando duas estratégias de tratamento de colisões:
- **Encadeamento Separado**
- **Sondagem Linear**
- **Sondagem Quadrática**
- **Duplo Hashing**

O objetivo é analisar e comparar o desempenho de ambas as técnicas em termos de tempo de execução e número de colisões durante operações de inserção, busca e remoção.

## Objetivos de Aprendizagem

- Compreender o funcionamento de tabelas hash
- Implementar funções de hash e mecanismos de tratamento de colisão
- Analisar desempenho de diferentes técnicas

## Estrutura do Projeto

```
├── functions/
│   ├── encadeamento_separado.c    # Implementação com encadeamento separado
│   ├── sondagem_linear.c          # Implementação com sondagem linear
│   ├── sondagem_quadratica.c      # Implementação com sondagem quadrática
│   ├── sondagem_dupla.c           # Implementação com Hash Duplo
│   ├── hashing.h                  # Função de hash e utilitários
│   └── functions_headers.h        # Headers das funções
├── BENCHMARK_functions/
│   ├── BENCHMARK_inserir.c        # Benchmark de inserção
│   ├── BENCHMARK_buscar.c         # Benchmark de busca
│   └── BENCHMARK_remover.c        # Benchmark de remoção
├── src/
│   ├── main.c                     # Programa principal
│   └── hash.h                     # Header principal
├── Execution_Reports/             # Pasta dos Relatorios
│
└── readme.md
```

## Implementações

### Função de Hash
Utiliza o método da multiplicação com a constante áurea (φ - 1 ≈ 0.618):
```c
int hashing(int chave) {
    double GR = 0.61803398875;
    double k_A_mod1 = ((chave * GR) - (int)(chave * GR));
    return (int)(tamanho * k_A_mod1);
}

int hashing2(int chave){
    return 1 + (chave % (tamanho));
}
```

### Encadeamento Separado
- **Estrutura**: Lista ligada em cada posição da tabela
- **Vantagem**: Sem limitação de elementos
- **Desvantagem**: Uso adicional de memória para ponteiros

### Sondagem Linear
- **Estrutura**: Array com status ('O'cupado, 'R'emovido, 'L'ivre)
- **Vantagem**: Uso eficiente de memória
- **Desvantagem**: O agrupamento de elementos pode degradar a performance

### Sondagem Quadrática
- **Estrutura**: Array com sondagem i² para resolução de colisões
- **Vantagem**: Reduz o agrupamento primário da sondagem linear
- **Desvantagem**: Pode sofrer de agrupamento secundário secundário

### Sondagem Dupla
- **Estrutura**: Utiliza duas funções hash para calcular o passo
- **Vantagem**: Melhor distribuição
- **Desvantagem**: Mais complexa computacionalmente

## Como Compilar e Executar

```bash
# Download do projeto
git clone https://github.com/artursnog/L.ED2_project.git

# Compilar o projeto
gcc -o main src/main.c

# Executar
./main
```
