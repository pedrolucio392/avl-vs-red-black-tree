# Amazon Engineering Challenge: Árvores Balanceadas (AVL e Rubro-Negra)

## O Projeto

Durante o período da Black Friday, o sistema de logística da Amazon recebe um volume massivo de identificadores (IDs) de encomendas. Se esses IDs forem inseridos em uma Árvore Binária de Busca (BST) comum, a ordem de chegada (ex: sequencial) pode causar a degeneração da estrutura para uma lista encadeada (O(n)). Dessa forma, este projeto implementa e avalia duas estruturas de dados auto-balanceáveis: **Árvore AVL** e **Árvore Rubro-Negra (LLRB)** com as operações de busca, inserção e remoção no tempo O(log n).

## Funcionalidades

- **Menu Interativo:** Escolha entre testar a Árvore AVL, a Rubro-Negra ou rodar o Benchmark automatizado.
- **Inserção e Remoção:** Tratamento de rebalanceamento e recoloração automáticos (sem o uso de bibliotecas externas).
- **Busca:** Verificação de existência de pacotes (IDs) em tempo logarítmico.
- **Percurso Em-Ordem:** Exibição dos IDs ordenados de forma crescente.
- **Visualização Estrutural (Print Tree):** Impressão da árvore deitada no terminal, exibindo o Fator de Balanceamento na AVL e as cores (Rubro/Negro) na LLRB com formatação ANSI.
- **Benchmark Automatizado:** Avaliação de 10.000 elementos nos cenários Crescente, Decrescente e Aleatório, exportando resultados (altura, rotações e tempo em ms) para um arquivo CSV.

## Pré-requisitos

Para compilar e executar o código, você precisará de:

- Compilador **G++** com suporte ao padrão **C++17**.
- Ferramenta **Make** (no Windows, recomenda-se `mingw32-make`).
- Terminal com suporte nativo a cores ANSI (recomendado: Windows Terminal, VS Code Terminal ou PowerShell).

## Como Compilar e Executar

1. **Clone o repositório:**

```bash
git clone https://github.com/pedrolucio392/avl-vs-red-black-tree.git
cd avl-vs-red-black-tree
```

2. **Compile o projeto (utilizando o Makefile):**
- No **Linux / macOS**:

```bash
make
```

- No **Windows** (com MinGW):

```bash
mingw32-make
```

3. **Execute o programa:**
   - No **Linux / macOS**:

```bash
make run
```

_(ou execute diretamente com `./output/main`)_

- No **Windows**:

```bash
mingw32-make run
```

_(ou execute diretamente com `./output/main.exe`)_

4. **Limpeza dos arquivos gerados (opcional):**
- No **Linux / macOS**: `make clean`
- No **Windows**: `mingw32-make clean`
