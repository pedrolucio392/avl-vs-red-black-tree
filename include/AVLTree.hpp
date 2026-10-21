#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "AVLNode.hpp"

class AVLTree
{
public:
    AVLNode *root;
    int rotationCount = 0;

    AVLTree() : root(nullptr) {}

    // retorna true se a chave especificada estiver presente na árvore ou false caso contrário
    bool search(int key)
    {
        return searchHelper(root, key);
    };

    // retorna o nó com a chave especificada (de forma recursiva) ou nullptr se não encontrado
    bool searchHelper(AVLNode *node, int key)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (node->key == key)
        {
            return true;
        }

        if (key < node->key)
        {
            return searchHelper(node->left, key);
        }
        else
        {
            return searchHelper(node->right, key);
        }
    };

    // metodo para inserir uma nova chave na árvore
    void insert(int key)
    {
        root = insertHelper(root, key);
    };

    // metodo auxiliar para inserir um nó na árvore (de forma recursiva)
    AVLNode *insertHelper(AVLNode *node, int key)
    {
        // Se o nó atual for nulo cria um novo nó com a chave especificada
        if (node == nullptr)
        {
            return new AVLNode(key);
        }

        // se a chave for menor que a chave do nó atual insere na subárvore esquerda, se não insere na subárvore direita
        if (key < node->key)
        {
            node->left = insertHelper(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = insertHelper(node->right, key);
        }
        else
        {
            return node; // Chave duplicada não isertir
        }

        updateHeight(node); // Atualiza a altura do nó atual

        int balanceFactor = getBalanceFactor(node); // Calcula o fator de balanceamento do nó atual

        if (balanceFactor > 1 && key < node->left->key) // Caso Left Left
        {
            return rotateRight(node);
        }
        if (balanceFactor < -1 && key > node->right->key) // Caso Right Right
        {
            return rotateLeft(node);
        }
        if (balanceFactor > 1 && key > node->left->key) // Caso Left Right
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balanceFactor < -1 && key < node->right->key) // Caso Right Left
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node; // Retorna o nó atual se não tiver alteração
    };

    // metodo para realizar a rotação à esquerda em um nó específico
    AVLNode *rotateLeft(AVLNode *node)
    {
        AVLNode *newRoot = node->right;       // Armazena o novo nó raiz (subárvore direita)
        AVLNode *subTreeLeft = newRoot->left; // Armazena a subárvore esquerda do novo nó raiz

        newRoot->left = node;      // Faz o nó atual se tornar a subárvore esquerda do novo nó raiz
        node->right = subTreeLeft; // Faz a subárvore esquerda do novo nó raiz se tornar a subárvore direita do nó atual

        updateHeight(node);    // Atualiza a altura do nó atual
        updateHeight(newRoot); // Atualiza a altura do novo nó raiz

        rotationCount++; // Incrementa o contador de rotações

        return newRoot;
    };

    // metodo para realizar a rotação à direita em um nó específico
    AVLNode *rotateRight(AVLNode *node)
    {
        AVLNode *newRoot = node->left;          // Armazena o novo nó raiz (subárvore esquerda)
        AVLNode *subTreeRight = newRoot->right; // Armazena a subárvore direita do novo nó raiz

        newRoot->right = node;     // Faz o nó atual se tornar a subárvore direita do novo nó raiz
        node->left = subTreeRight; // Faz a subárvore direita do novo nó raiz se tornar a subárvore esquerda do nó atual

        updateHeight(node);    // Atualiza a altura do nó atual
        updateHeight(newRoot); // Atualiza a altura do novo nó raiz

        rotationCount++; // Incrementa o contador de rotações

        return newRoot;
    };

    void remove(int key);

    // retorna a altura do nó especificado, ou 0 se o nó for nulo
    int getNodeHeight(AVLNode *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    };

    // retorna a altura da árvore inteira que é a altura do root
    int getTreeHeight()
    {
        return getNodeHeight(root);
    };

    void inOrder();
    void printTree();
    void getRotationCount();

    int getBalanceFactor(AVLNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return getNodeHeight(node->left) - getNodeHeight(node->right);
    };

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    void updateHeight(AVLNode *node)
    {
        node->height = 1 + max(getNodeHeight(node->left), getNodeHeight(node->right));
    }
};

#endif