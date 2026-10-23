#include <iostream>
#include <cassert>
#include "RBTree.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

void testBasicSearch()
{
    std::cout << "Teste de inserção e Search..." << std::endl;
    RBTree tree;

    assert(tree.getRoot() == nullptr);
    assert(!tree.search(10));

    tree.insert(10);
    tree.printTree();
    tree.insert(20);
    tree.printTree();
    tree.insert(5);
    tree.printTree();

    assert(tree.getRoot() != nullptr);
    assert(tree.search(10));
    assert(tree.search(20));
    assert(tree.search(5));
    assert(!tree.search(99)); // Valor inexistente

    std::cout << "Passou com sucesso!\n"
              << std::endl;
}

void testRightLeaningFix()
{
    std::cout << "Teste de correcao de inclinacao a direita" << std::endl;
    RBTree tree;

    // Inserir 10 e depois 20 forçaria um filho direito vermelho.
    // A LLRB deve aplicar rotateLeft
    tree.insert(10);
    assert(tree.getRotationCount() == 0);

    tree.insert(20);
    // Deve ter ocorrido pelo menos 1 rotacao a esquerda
    assert(tree.getRotationCount() == 1);
    assert(tree.search(10));
    assert(tree.search(20));

    std::cout << "-> Passou com sucesso! Rotacoes: " << tree.getRotationCount() << "\n"
              << std::endl;
}

void testConsecutiveRedsFix()
{
    std::cout << "Testar conflito de dois vermelhos seguidos" << std::endl;
    RBTree tree;

    // Inserção em ordem decrescente (30, 20, 10):
    // 30 -> raiz (preta)
    // 20 -> filho esquerdo (vermelho)
    // 10 -> filho esquerdo do 20 (vermelho) -> Dispara rotateRight + flipColors!
    tree.insert(30);
    tree.printTree();
    tree.insert(20);
    tree.printTree();
    tree.insert(10);

    assert(tree.search(30));
    assert(tree.search(20));
    assert(tree.search(10));

    // Exibicao visual para inspecionar a arvore
    std::cout << "Visualizacao da arvore apos inserir 30, 20, 10:\n";
    tree.printTree();

    std::cout << "\n-> Passou com sucesso! Total de rotacoes: " << tree.getRotationCount() << "\n"
              << std::endl;
}

void testDuplicateKeys()
{
    std::cout << "Teste de chaves duplicadas" << std::endl;
    RBTree tree;

    tree.insert(15);
    tree.insert(15);
    tree.insert(15);

    assert(tree.search(15));
    std::cout << "-> Passou com sucesso!\n"
              << std::endl;
}

int main()
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    std::cout << "=== INICIANDO TESTES: LLRB ===\n\n";

    testBasicSearch();
    testRightLeaningFix();
    testConsecutiveRedsFix();
    testDuplicateKeys();

    std::cout << "=== TODOS OS TESTES PASSARAM! ===\n";
    return 0;
}