#include <iostream>
#include <cassert>
#include "AVLTree.hpp"

void testRemoveLeaf()
{
    std::cout << "Testando Remocao de No Folha" << std::endl;
    AVLTree tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);

    // Remove a folha 10
    tree.remove(10);

    assert(tree.search(10) == false);
    assert(tree.search(20) == true);
    assert(tree.search(30) == true);
    assert(tree.root->key == 20);
    assert(tree.root->left == nullptr);
    assert(tree.getTreeHeight() == 2);
    std::cout << "-> Remocao de folha aprovada!\n"
              << std::endl;
}

void testRemoveNodeWithOneChild()
{
    std::cout << "Testando Remocao de No com 1 Filho..." << std::endl;
    AVLTree tree;
    // Arvore 20 -> filho esq 10 -> filho esq 5
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5); // 10 agora tem 1 filho (5) e nenhum a direita

    // Remove o no 10 (tem apenas 1 filho: 5)
    tree.remove(10);

    assert(tree.search(10) == false);
    assert(tree.search(5) == true);
    assert(tree.root->left != nullptr);
    assert(tree.root->left->key == 5); // 5 subiu para o lugar do 10
    std::cout << "-> Remocao de no com 1 filho aprovada!\n"
              << std::endl;
}

void testRemoveNodeWithTwoChildren()
{
    std::cout << "Testando Remocao de No com 2 Filhos (Raiz)..." << std::endl;
    AVLTree tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(25);
    tree.insert(40);

    // Remove a raiz 20 (tem 2 filhos: 10 e 30)
    tree.remove(20);

    assert(tree.search(20) == false);
    assert(tree.root->key == 25); // 25 virou a nova raiz
    assert(tree.root->left->key == 10);
    assert(tree.root->right->key == 30);
    assert(tree.search(25) == true);
    assert(tree.search(30) == true);
    assert(tree.search(40) == true);
    std::cout << "-> Remocao de no com 2 filhos aprovada!\n"
              << std::endl;
}

void testRemoveCausingRebalance()
{
    std::cout << "Testando Remocao com Rebalanceamento (Rotacao Simples)..." << std::endl;
    AVLTree tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(10);

    int rotacoesAntes = tree.rotationCount;

    // Remover 40 torna a subarvore direita nula.
    // O no 30 fica com FB = 2 e filho esquerdo (20) com FB >= 0 -> Dispara rotateRight(30)
    tree.remove(40);

    assert(tree.search(40) == false);
    assert(tree.root->key == 20); // 20 assumiu o topo
    assert(tree.root->left->key == 10);
    assert(tree.root->right->key == 30);
    assert(tree.getTreeHeight() == 2);
    assert(tree.rotationCount > rotacoesAntes); // Garante que rebalanceou
    std::cout << "-> Rebalanceamento por remocao aprovado!\n"
              << std::endl;
}

void testRemoveNonExistentAndEmpty()
{
    std::cout << "Testando Casos de Borda (Inexistente e Esvaziamento)..." << std::endl;
    AVLTree tree;
    tree.insert(50);

    // Chave que nao existe em arvore com elementos
    tree.remove(999);
    assert(tree.root != nullptr && tree.root->key == 50);

    // Remove o unico elemento
    tree.remove(50);
    assert(tree.root == nullptr);
    assert(tree.getTreeHeight() == 0);

    // Remover em arvore ja vazia
    tree.remove(50);
    assert(tree.root == nullptr);
    std::cout << "-> Casos de borda aprovados!\n"
              << std::endl;
}

int main()
{
    testRemoveLeaf();
    testRemoveNodeWithOneChild();
    testRemoveNodeWithTwoChildren();
    testRemoveCausingRebalance();
    testRemoveNonExistentAndEmpty();

    std::cout << "TODOS OS TESTES DE REMOCAO PASSARAM COM SUCESSO!" << std::endl;
    return 0;
}