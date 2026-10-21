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

    // remove um nó com a chave especificada da árvore
    void remove(int key)
    {
        root = removeHelper(root, key);
    };

    // remove um nó com a chave especificada da árvore (de forma recursiva)
    AVLNode *removeHelper(AVLNode *node, int key)
    {
        if (node == nullptr)
        {
            return node; // Nó não encontrado
        }

        if (key < node->key)
        {
            node->left = removeHelper(node->left, key); // Procura na subárvore esquerda
        }
        else if (key > node->key)
        {
            node->right = removeHelper(node->right, key); // Procura na subárvore direita
        }
        else
        {
            // Nó encontrado, realiza a remoção
            if (node->left == nullptr || node->right == nullptr)
            {
                AVLNode *temp = node->left ? node->left : node->right;

                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr; // Nó sem filhos
                }
                else
                {
                    *node = *temp; // Nó com um filho
                }

                delete temp;
            }
            else
            {
                AVLNode *temp = getMinValueNode(node->right); // Nó com dois filhos

                node->key = temp->key; // Substitui a chave pelo menor valor da subárvore direita

                node->right = removeHelper(node->right, temp->key); // Remove o nó substituído
            }
        }

        if (node == nullptr)
        {
            return node; // Retorna se o nó for nulo após a remoção
        }

        updateHeight(node); // Atualiza a altura do nó atual

        int balanceFactor = getBalanceFactor(node); // Calcula o fator de balanceamento do nó atual

        if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) // Caso Left Left
        {
            return rotateRight(node);
        }
        if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) // Caso Right Right
        {
            return rotateLeft(node);
        }
        if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) // Caso Left Right
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) // Caso Right Left
        {
            node->right = rotateRight(node);
            return rotateLeft(node);
        }
        return node; // Retorna o nó atual se não tiver alteração
    };

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

    // retorna o fator de balanceamento do nó, ou 0 se o nó for nulo
    int getBalanceFactor(AVLNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return getNodeHeight(node->left) - getNodeHeight(node->right);
    };

    // retorna o maior valor entre dois inteiros
    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    // atualiza a altura do nó especificado com base nas alturas de seus filhos
    void updateHeight(AVLNode *node)
    {
        node->height = 1 + max(getNodeHeight(node->left), getNodeHeight(node->right));
    }

    // pega o menor nó da subárvore especificada (usado para encontrar o sucessor in-order)
    AVLNode *getMinValueNode(AVLNode *node)
    {
        AVLNode *current = node;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }
};

#endif