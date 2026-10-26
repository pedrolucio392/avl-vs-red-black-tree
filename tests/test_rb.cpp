#include <iostream>
#include <cassert>
#include "RBTree.hpp"
#include <vector>

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

void testRemoveLeaf() {
    std::cout << "[TESTE REMOVE 1] Remocao de folhas..." << std::endl;
    RBTree tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(30);

    assert(tree.search(10));
    tree.remove(10);
    assert(!tree.search(10));
    assert(tree.search(20));
    assert(tree.search(30));

    tree.remove(30);
    assert(!tree.search(30));
    assert(tree.search(20));

    std::cout << "-> Passou!\n" << std::endl;
}

void testRemoveNodeWithTwoChildren() {
    std::cout << "[TESTE REMOVE 2] Remocao de no interno com dois filhos..." << std::endl;
    RBTree tree;

    // Constrói uma árvore balanceada
    std::vector<int> values = {50, 20, 70, 10, 30, 60, 80};
    for (int v : values) {
        tree.insert(v);
    }

    std::cout << "Arvore antes de remover o 20:\n";
    tree.printTree();

    // 20 possui filhos 10 e 30
    tree.remove(20);
    assert(!tree.search(20));
    assert(tree.search(10));
    assert(tree.search(30));
    assert(tree.search(50));
    assert(tree.search(70));

    std::cout << "\nArvore apos remover o 20 (sucessor assumiu):\n";
    tree.printTree();

    std::cout << "-> Passou!\n" << std::endl;
}

// Teste 3: Remoção da própria Raiz
void testRemoveRoot() {
    std::cout << "[TESTE REMOVE 3] Remocao da raiz..." << std::endl;
    RBTree tree;

    tree.insert(40);
    tree.insert(20);
    tree.insert(60);

    // Remove a raiz
    tree.remove(40);
    assert(!tree.search(40));
    assert(tree.search(20));
    assert(tree.search(60));

    // Remove a nova raiz
    tree.remove(60);
    assert(!tree.search(60));
    assert(tree.search(20));

    // Remove o último elemento restante
    tree.remove(20);
    assert(!tree.search(20));
    assert(tree.getRoot() == nullptr);

    std::cout << "-> Passou!\n" << std::endl;
}

// Teste 4: Chave inexistente (não deve quebrar nem alterar nada)
void testRemoveNonExistent() {
    std::cout << "[TESTE REMOVE 4] Remocao de chave inexistente..." << std::endl;
    RBTree tree;

    tree.insert(10);
    tree.insert(5);

    tree.remove(99); // Não existe
    assert(tree.search(10));
    assert(tree.search(5));

    std::cout << "-> Passou!\n" << std::endl;
}

// Teste 5: Estresse - Inserções e remoções em cascata
void testStressRemove() {
    std::cout << "[TESTE REMOVE 5] Teste de estresse com multiplas remocoes..." << std::endl;
    RBTree tree;
    std::vector<int> dataset = {15, 8, 25, 4, 11, 20, 30, 2, 6, 9, 13};

    for (int x : dataset) {
        tree.insert(x);
    }

    // Remove metade dos elementos
    std::vector<int> toRemove = {4, 25, 15, 2};
    for (int x : toRemove) {
        tree.remove(x);
        assert(!tree.search(x));
    }

    // Confere se os outros continuam intactos
    std::vector<int> remaining = {8, 11, 20, 30, 6, 9, 13};
    for (int x : remaining) {
        assert(tree.search(x));
    }

    std::cout << "Arvore resultante do estresse:\n";
    tree.printTree();

    std::cout << "-> Passou!\n" << std::endl;
}

int main()
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    std::cout << "=== INICIANDO TESTES: LLRB ===\n\n";

    // testBasicSearch();
    // testRightLeaningFix();
    // testConsecutiveRedsFix();
    // testDuplicateKeys();

    testRemoveLeaf();
    testRemoveNodeWithTwoChildren();
    testRemoveRoot();
    testRemoveNonExistent();
    testStressRemove();

    std::cout << "=== TODOS OS TESTES PASSARAM! ===\n";
    return 0;
}