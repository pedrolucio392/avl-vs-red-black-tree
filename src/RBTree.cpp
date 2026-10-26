#include "RBTree.hpp"

#include <iostream>
#include <string>
#include <algorithm>

#define ANSI_RED "\033[31;1m"
#define ANSI_RESET "\033[0m"

RBTree::RBTree() : root(nullptr), rotationCount(0) {}

RBTree::~RBTree()
{
    destroyTree(root);
    root = nullptr;
};

// METODOS PRIVADOS

// METODOS PRINCIPAIS PRIVADOS

// retorna o nó com a chave especificada (de forma recursiva) ou nullptr se não encontrado
bool RBTree::search(RBNode *node, int key) const
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
        return search(node->left, key);
    }
    else
    {
        return search(node->right, key);
    }
};

// insere um nó com a chave especificada na árvore recursivamente
RBNode *RBTree::insert(RBNode *node, int key)
{
    if (node == nullptr)
    {
        return new RBNode(key);
    }

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
        return node; // Chave duplicada não inserir
    }

    if (isRed(node->right) && !isRed(node->left))
    {
        node = rotateLeft(node);
    }
    if (isRed(node->left) && isRed(node->left->left))
    {
        node = rotateRight(node);
    }
    if (isRed(node->left) && isRed(node->right))
    {
        flipColors(node);
    }

    return node; // Retorna o nó atual se não tiver alteração
};

// lógica principal recursiva para remoção na rb
RBNode *RBTree::remove(RBNode *node, int key)
{
    if (key < node->key)
    {
        if (!isRed(node->left) && !isRed(node->left->left))
        {
            node = moveRedLeft(node);
        }
        node->left = remove(node->left, key);
    }
    else
    {
        // Se houver um link vermelho à esquerda, rotaciona para a direita
        if (isRed(node->left))
        {
            node = rotateRight(node);
        }

        if (key == node->key && (node->right == nullptr))
        {
            delete node;
            return nullptr;
        }

        if (!isRed(node->right) && !isRed(node->right->left))
        {
            node = moveRedRight(node);
        }

        // Nó interno encontrado com subárvore direita
        if (key == node->key)
        {
            RBNode *minNode = getMinimum(node->right);
            node->key = minNode->key;
            node->right = removeMin(node->right);
        }
        else
        {
            node->right = remove(node->right, key);
        }
    }

    // Rebalanceia na subida da recursão
    return balance(node);
}

// METODOS AUXILIARES PRIVADOS

// realiza a rotação à esquerda em um nó específico
RBNode *RBTree::rotateLeft(RBNode *node)
{
    RBNode *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    newRoot->color = node->color;
    node->color = RED;

    rotationCount++;
    return newRoot;
};

// realiza a rotação à direita em um nó específico
RBNode *RBTree::rotateRight(RBNode *node)
{
    RBNode *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    newRoot->color = node->color;
    node->color = RED;

    rotationCount++;
    return newRoot;
};

// retorna se é vermelho ou não
bool RBTree::isRed(RBNode *node) const
{
    return node != nullptr && node->color == RED;
};

// realiza a troca das cores dos nós
void RBTree::flipColors(RBNode *node)
{
    node->color = (node->color == RED) ? BLACK : RED;
    node->left->color = (node->left->color == RED) ? BLACK : RED;
    node->right->color = (node->right->color == RED) ? BLACK : RED;
};

// metodo para balancear a RB tree nos diferentes casos (ambos filhos vermelhos, etc)
RBNode *RBTree::balance(RBNode *node)
{
    if (isRed(node->right) && !isRed(node->left))
    {
        node = rotateLeft(node);
    }
    if (isRed(node->left) && isRed(node->left->left))
    {
        node = rotateRight(node);
    }
    if (isRed(node->left) && isRed(node->right))
    {
        flipColors(node);
    }
    return node;
};

// auxiliar de remoção
RBNode *RBTree::moveRedLeft(RBNode *node)
{
    flipColors(node);
    if (isRed(node->right->left))
    {
        node->right = rotateRight(node->right);
        node = rotateLeft(node);
        flipColors(node);
    }
    return node;
};

// auxiliar de remoção
RBNode *RBTree::moveRedRight(RBNode *node)
{
    flipColors(node);
    // Se o irmão esquerdo tem um filho esquerdo vermelho, empresta dele
    if (isRed(node->left->left))
    {
        node = rotateRight(node);
        flipColors(node);
    }
    return node;
};

//
RBNode *RBTree::getMinimum(RBNode *node) const
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
};

int RBTree::height(RBNode *node) const
{
    if (node == nullptr)
        return 0;
    return 1 + std::max(height(node->left), height(node->right));
}

//
RBNode *RBTree::removeMin(RBNode *node)
{
    if (node->left == nullptr)
    {
        delete node;
        return nullptr;
    }

    if (!isRed(node->left) && !isRed(node->left->left))
    {
        node = moveRedLeft(node);
    }

    node->left = removeMin(node->left);
    return balance(node);
};

// destroi a árvore utilizando pós-ordem
void RBTree::destroyTree(RBNode *node)
{
    if (node == nullptr)
    {
        return;
    }

    destroyTree(node->left);
    destroyTree(node->right);

    delete node;
};

// mostra a árvore final
void RBTree::printTree(RBNode *node, const std::string &prefix, bool isLeft) const
{
    if (node == nullptr)
    {
        return;
    }

    // Visita a subárvore direita primeiro (topo do terminal)
    printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);

    // 2. Conector visual
    std::cout << prefix;
    std::cout << (isLeft ? "└── " : "┌── ");

    // 3. Chave com cor e indicador [R] ou [B]
    if (node->color == RED)
    {
        std::cout << ANSI_RED << node->key << " [R]" << ANSI_RESET << "\n";
    }
    else
    {
        std::cout << node->key << " [B]\n";
    }

    // 4. Visita a subárvore esquerda (baixo do terminal)
    printTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
}

// METODOS PUBLICOS

bool RBTree::search(int key) const
{
    return search(root, key);
};

void RBTree::insert(int key)
{
    root = insert(root, key);
    root->color = BLACK; // A raiz deve ser sempre preta
};

RBNode *RBTree::getRoot() const
{
    return root;
};

int RBTree::getRotationCount() const
{
    return rotationCount;
};

void RBTree::printTree() const
{
    if (root == nullptr)
    {
        std::cout << "(arvore vazia)\n";
        return;
    }
    printTree(root, "", false);
}

// Metodo de remoção público
void RBTree::remove(int key)
{
    if (root == nullptr || !search(key))
    {
        return;
    }

    if (!isRed(root->left) && !isRed(root->right))
    {
        root->color = RED;
    }

    root = remove(root, key);

    if (root != nullptr)
    {
        root->color = BLACK;
    }
}

int RBTree::height() const
{
    return height(root);
}