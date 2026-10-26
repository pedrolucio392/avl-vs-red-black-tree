#include "AVLTree.hpp"
#include <iostream>
#include <string>

// Inicializa a arvore AVL vazia
AVLTree::AVLTree() : root(nullptr), rotationCount(0) {}

// Destrutor padrao que limpa todos os nos
AVLTree::~AVLTree()
{
    clear();
}

// Remove todos os elementos da arvore
void AVLTree::clear()
{
    destroyAVL(root);
    root = nullptr;
}

// Auxiliar recursivo para desalocar nos da memoria
void AVLTree::destroyAVL(AVLNode *node)
{
    if (node != nullptr)
    {
        destroyAVL(node->left);
        destroyAVL(node->right);
        delete node;
    }
}

// Retorna a altura total da arvore
int AVLTree::height() const
{
    return height(root);
}

// Retorna a altura de um no especifico de forma segura
int AVLTree::height(AVLNode *node) const
{
    return node == nullptr ? 0 : node->height;
}

// Calcula o fator de balanceamento de um no
int AVLTree::getBalance(AVLNode *node) const
{
    return node == nullptr ? 0 : height(node->left) - height(node->right);
}

// Atualiza a altura do no com base nos seus filhos
void AVLTree::updateHeight(AVLNode *node)
{
    if (node != nullptr)
    {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

// Retorna o contador total de rotacoes realizadas
int AVLTree::getRotationCount() const
{
    return rotationCount;
}

// Zera o contador de rotacoes
void AVLTree::resetRotationCount()
{
    rotationCount = 0;
}

// Busca publica por uma chave na arvore
bool AVLTree::search(int key) const
{
    return search(root, key);
}

// Busca recursiva por uma chave
bool AVLTree::search(AVLNode *node, int key) const
{
    if (node == nullptr)
        return false;
    if (key < node->key)
        return search(node->left, key);
    if (key > node->key)
        return search(node->right, key);
    return true;
}

// Realiza a rotacao simples a direita
AVLNode *AVLTree::rotateRight(AVLNode *node)
{
    if (node == nullptr || node->left == nullptr)
        return node;
    AVLNode *leftChild = node->left;
    AVLNode *rightOfLeft = leftChild->right;

    leftChild->right = node;
    node->left = rightOfLeft;

    updateHeight(node);
    updateHeight(leftChild);
    rotationCount++;
    return leftChild;
}

// Realiza a rotacao simples a esquerda
AVLNode *AVLTree::rotateLeft(AVLNode *node)
{
    if (node == nullptr || node->right == nullptr)
        return node;
    AVLNode *rightChild = node->right;
    AVLNode *leftOfRight = rightChild->left;

    rightChild->left = node;
    node->right = leftOfRight;

    updateHeight(node);
    updateHeight(rightChild);
    rotationCount++;
    return rightChild;
}

// Insere uma nova chave na arvore
void AVLTree::insert(int key)
{
    root = insert(root, key);
}

// Auxiliar recursivo para inserir uma chave e balancear a arvore
AVLNode *AVLTree::insert(AVLNode *node, int key)
{
    if (node == nullptr)
        return new AVLNode(key);

    if (key < node->key)
    {
        node->left = insert(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key);
    }
    else
    {
        return node;
    }

    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    if (balance > 1 && key > node->left->key)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Remove uma chave da arvore
void AVLTree::remove(int key)
{
    root = remove(root, key);
}

// Encontra o no com o menor valor (mais a esquerda)
AVLNode *AVLTree::getMin(AVLNode *node) const
{
    AVLNode *current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

// Auxiliar recursivo para remover uma chave e rebalancear a arvore
AVLNode *AVLTree::remove(AVLNode *node, int key)
{
    if (node == nullptr)
        return nullptr;

    if (key < node->key)
    {
        node->left = remove(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = remove(node->right, key);
    }
    else
    {
        if (node->left == nullptr)
        {
            AVLNode *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            AVLNode *temp = node->left;
            delete node;
            return temp;
        }

        AVLNode *temp = getMin(node->right);
        node->key = temp->key;
        node->right = remove(node->right, temp->key);
    }

    if (node == nullptr)
        return nullptr;

    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rotateRight(node);
    if (balance > 1 && getBalance(node->left) < 0)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0)
        return rotateLeft(node);
    if (balance < -1 && getBalance(node->right) > 0)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Percurso em ordem (crescente)
void AVLTree::printInOrder() const
{
    printInOrder(root);
    std::cout << "\n";
}

void AVLTree::printInOrder(AVLNode *node) const
{
    if (node != nullptr)
    {
        printInOrder(node->left);
        std::cout << node->key << " ";
        printInOrder(node->right);
    }
}

void AVLTree::printTree() const
{
    if (root == nullptr)
    {
        std::cout << "(arvore vazia)\n";
        return;
    }
    printTree(root, "", false);
}

void AVLTree::printTree(AVLNode *node, const std::string &prefix, bool isLeft) const
{
    if (node == nullptr)
    {
        return;
    }

    // Visita a subárvore direita primeiro (topo do terminal)
    printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);

    // Conector visual
    std::cout << prefix;
    std::cout << (isLeft ? "└── " : "┌── ");

    // Chave com o Fator de Balanceamento
    std::cout << node->key << " (FB: " << getBalance(node) << ")\n";

    // Visita a subárvore esquerda (baixo do terminal)
    printTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
}