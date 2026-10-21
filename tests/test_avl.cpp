#include <iostream>
#include <cassert>
#include "AVLTree.hpp"

void testLeftLeft()
{
    std::cout << "Testando Caso LL" << std::endl;
    AVLTree tree;
    // 30, 20, 10
    tree.insert(30);
    tree.insert(20);
    tree.insert(10); // Deve disparar rotateRight em 30

    assert(tree.root != nullptr);
    assert(tree.root->key == 20); // 20 virou a nova raiz
    assert(tree.root->left->key == 10);
    assert(tree.root->right->key == 30);
    assert(tree.getTreeHeight() == 2); // Considerando folha = 1
    assert(tree.rotationCount == 1);   // Exatamente 1 rotação realizada
    std::cout << "-> Caso LL aprovado!\n"
              << std::endl;
}

void testRightRight()
{
    std::cout << "Testando Caso RR (Rotacao Simples a Esquerda)..." << std::endl;
    AVLTree tree;
    // Inserção estritamente crescente: 10, 20, 30
    tree.insert(10);
    tree.insert(20);
    tree.insert(30); // Deve disparar rotateLeft em 10

    assert(tree.root != nullptr);
    assert(tree.root->key == 20); // 20 virou a nova raiz
    assert(tree.root->left->key == 10);
    assert(tree.root->right->key == 30);
    assert(tree.getTreeHeight() == 2);
    assert(tree.rotationCount == 1);
    std::cout << "-> Caso RR aprovado!\n"
              << std::endl;
}

void testLeftRight()
{
    std::cout << "Testando Caso LR (Rotacao Dupla: Esquerda-Direita)..." << std::endl;
    AVLTree tree;
    // Sequência em zig-zag: 30, 10, 20
    tree.insert(30);
    tree.insert(10);
    tree.insert(20); // 10 roda a esquerda, depois 30 roda a direita

    assert(tree.root != nullptr);
    assert(tree.root->key == 20); // 20 deve ser a raiz final
    assert(tree.root->left->key == 10);
    assert(tree.root->right->key == 30);
    assert(tree.getTreeHeight() == 2);
    assert(tree.rotationCount == 2); // Contabiliza 2 rotações simples
    std::cout << "-> Caso LR aprovado!\n"
              << std::endl;
}

void testRightLeft()
{
    std::cout << "Testando Caso RL (Rotacao Dupla: Direita-Esquerda)..." << std::endl;
    AVLTree tree;
    // Sequência em zig-zag: 10, 30, 20
    tree.insert(10);
    tree.insert(30);
    tree.insert(20); // 30 roda a direita, depois 10 roda a esquerda

    assert(tree.root != nullptr);
    assert(tree.root->key == 20);
    assert(tree.root->left->key == 10);
    assert(tree.root->right->key == 30);
    assert(tree.getTreeHeight() == 2);
    assert(tree.rotationCount == 2);
    std::cout << "-> Caso RL aprovado!\n"
              << std::endl;
}

void testDuplicates()
{
    std::cout << "Testando Insercao de Duplicatas..." << std::endl;
    AVLTree tree;
    tree.insert(15);
    tree.insert(15); // Tentativa de inserir a mesma chave

    assert(tree.getTreeHeight() == 1);
    assert(tree.root->left == nullptr);
    assert(tree.root->right == nullptr);
    std::cout << "-> Tratamento de duplicatas aprovado!\n"
              << std::endl;
}

int main()
{
    testLeftLeft();
    testRightRight();
    testLeftRight();
    testRightLeft();
    testDuplicates();

    std::cout << "Todos os casos de teste de insercao passaram com sucesso!" << std::endl;
    return 0;
}