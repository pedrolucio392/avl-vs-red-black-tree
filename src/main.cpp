#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h>

#include "AVLTree.hpp"
#include "RBTree.hpp"

// --- ESTRUTURAS E FUNÇÕES DO BENCHMARK ---
struct BenchmarkResult
{
    std::string treeName, scenario, operation;
    int dataSize, height, rotations;
    double timeMs;
};

void printResultsTable(const std::vector<BenchmarkResult> &results)
{
    std::cout << "\n"
              << std::string(90, '=') << "\n";
    std::cout << std::left << std::setw(10) << "Estrutura" << std::setw(16) << "Cenario"
              << std::setw(12) << "Operacao" << std::setw(10) << "N Itens"
              << std::setw(10) << "Altura" << std::setw(14) << "Rotacoes"
              << std::setw(14) << "Tempo (ms)" << "\n";
    std::cout << std::string(90, '-') << "\n";
    for (const auto &r : results)
    {
        std::cout << std::left << std::setw(10) << r.treeName << std::setw(16) << r.scenario
                  << std::setw(12) << r.operation << std::setw(10) << r.dataSize
                  << std::setw(10) << r.height << std::setw(14) << r.rotations
                  << std::setw(14) << std::fixed << std::setprecision(4) << r.timeMs << "\n";
    }
    std::cout << std::string(90, '=') << "\n\n";
}

void exportToCSV(const std::vector<BenchmarkResult> &results, const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << "Estrutura,Cenario,Operacao,N_Itens,Altura,Rotacoes,Tempo_ms\n";
        for (const auto &r : results)
        {
            file << r.treeName << "," << r.scenario << "," << r.operation << ","
                 << r.dataSize << "," << r.height << "," << r.rotations << ","
                 << std::fixed << std::setprecision(4) << r.timeMs << "\n";
        }
        file.close();
        std::cout << "-> Benchmark exportado para: " << filename << "\n";
    }
}

template <typename TreeType>
void runFullBenchmark(std::vector<BenchmarkResult> &results, const std::string &treeName,
                      const std::string &scenario, const std::vector<int> &data, const std::vector<int> &searchQueries)
{
    TreeType tree;

    // Inserção
    auto startInsert = std::chrono::high_resolution_clock::now();
    for (int val : data)
        tree.insert(val);
    auto endInsert = std::chrono::high_resolution_clock::now();
    results.push_back({treeName, scenario, "Insert", (int)data.size(), tree.height(), tree.getRotationCount(), std::chrono::duration<double, std::milli>(endInsert - startInsert).count()});

    // Busca
    auto startSearch = std::chrono::high_resolution_clock::now();
    volatile bool found = false;
    for (int val : searchQueries)
        found = tree.search(val);
    (void)found;
    auto endSearch = std::chrono::high_resolution_clock::now();
    results.push_back({treeName, scenario, "Search", (int)searchQueries.size(), tree.height(), 0, std::chrono::duration<double, std::milli>(endSearch - startSearch).count()});

    // Remoção
    int rotBefore = tree.getRotationCount();
    auto startRemove = std::chrono::high_resolution_clock::now();
    for (int val : data)
        tree.remove(val);
    auto endRemove = std::chrono::high_resolution_clock::now();
    results.push_back({treeName, scenario, "Remove", (int)data.size(), tree.height(), tree.getRotationCount() - rotBefore, std::chrono::duration<double, std::milli>(endRemove - startRemove).count()});
}

void runBenchmark()
{
    std::vector<BenchmarkResult> allResults;
    // Tamanhos de carga para o Teste de Estresse
    std::vector<int> N_values = {10000, 50000, 100000};

    std::cout << "\nIniciando Bateria de Testes de Estresse. Isso pode levar alguns segundos...\n";

    for (int N : N_values)
    {
        std::vector<int> queries(N), asc(N), desc(N), randData(N);

        std::iota(queries.begin(), queries.end(), 1);
        std::mt19937 gSearch(999);
        std::shuffle(queries.begin(), queries.end(), gSearch);

        std::iota(randData.begin(), randData.end(), 1);
        std::mt19937 g(42);
        std::shuffle(randData.begin(), randData.end(), g);

        std::iota(asc.begin(), asc.end(), 1);
        desc = asc;
        std::reverse(desc.begin(), desc.end());

        std::cout << "-> Processando Lote de " << N << " itens...\n";

        runFullBenchmark<AVLTree>(allResults, "AVL", "Aleatorio", randData, queries);
        runFullBenchmark<RBTree>(allResults, "LLRB", "Aleatorio", randData, queries);
        runFullBenchmark<AVLTree>(allResults, "AVL", "Crescente", asc, queries);
        runFullBenchmark<RBTree>(allResults, "LLRB", "Crescente", asc, queries);
        runFullBenchmark<AVLTree>(allResults, "AVL", "Decrescente", desc, queries);
        runFullBenchmark<RBTree>(allResults, "LLRB", "Decrescente", desc, queries);
    }

    printResultsTable(allResults);
    exportToCSV(allResults, "output/benchmark_results.csv");
    std::cout << "Bateria de testes concluida com sucesso!\n";
}

// --- MENU INTERATIVO ---
template <typename TreeType>
void menuInterativo(const std::string &nomeArvore)
{
    TreeType tree;
    int opcao = -1, valor;

    while (opcao != 0)
    {
        std::cout << "\n--- INTERACAO: " << nomeArvore << " ---\n";
        std::cout << "1. Inserir encomenda (ID)\n";
        std::cout << "2. Remover encomenda (ID)\n";
        std::cout << "3. Buscar encomenda (ID)\n";
        std::cout << "4. Exibir percurso Em-Ordem (Crescente)\n";
        std::cout << "5. Visualizar Estrutura da Arvore\n";
        std::cout << "0. Voltar ao Menu Principal\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao)
        {
        case 1:
            std::cout << "Digite o ID para inserir: ";
            std::cin >> valor;
            if (tree.search(valor))
            {
                std::cout << "[AVISO] ID " << valor << " ja existe. Insercao ignorada.\n";
            }
            else
            {
                tree.insert(valor);
                std::cout << "ID " << valor << " inserido com sucesso.\n";
            }
            break;
        case 2:
            std::cout << "Digite o ID para remover: ";
            std::cin >> valor;
            if (!tree.search(valor))
            {
                std::cout << "[AVISO] ID " << valor << " nao encontrado.\n";
            }
            else
            {
                tree.remove(valor);
                std::cout << "ID " << valor << " removido com sucesso.\n";
            }
            break;
        case 3:
            std::cout << "Digite o ID para buscar: ";
            std::cin >> valor;
            if (tree.search(valor))
                std::cout << "-> ID " << valor << " ENCONTRADO na arvore.\n";
            else
                std::cout << "-> ID " << valor << " NAO ENCONTRADO.\n";
            break;
        case 4:
            std::cout << "Elementos em ordem crescente:\n";
            tree.printInOrder();
            break;
        case 5:
            std::cout << "Estrutura da Arvore:\n";
            tree.printTree();
            break;
        case 0:
            break;
        default:
            std::cout << "Opcao invalida!\n";
        }
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int opcaoPrincipal = -1;

    while (opcaoPrincipal != 0)
    {
        std::cout << "\n=============================================\n";
        std::cout << " AMAZON ENGINEERING CHALLENGE - LOGISTICA\n";
        std::cout << "=============================================\n";
        std::cout << "1. Testar Arvore AVL\n";
        std::cout << "2. Testar Arvore Rubro-Negra (LLRB)\n";
        std::cout << "3. Executar Benchmark Completo (CSV)\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcaoPrincipal;

        switch (opcaoPrincipal)
        {
        case 1:
            menuInterativo<AVLTree>("Arvore AVL");
            break;
        case 2:
            menuInterativo<RBTree>("Arvore Rubro-Negra");
            break;
        case 3:
            runBenchmark();
            break;
        case 0:
            std::cout << "Encerrando o sistema...\n";
            break;
        default:
            std::cout << "Opcao invalida!\n";
        }
    }
    return 0;
}