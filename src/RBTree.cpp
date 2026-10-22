#include "RBTree.hpp"

#include <iostream>
#include <string>

RBTree::RBTree() : root(nullptr), rotationCount(0) {}

RBTree::~RBTree()
{
    destroyTree(root);
    root = nullptr;
}

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

// METODOS AUXILIARES PRIVADOS

bool RBTree::isRed(RBNode *node) const
{
    return node != nullptr && node->color == RED;
}

void RBTree::flipColors(RBNode *node)
{
    node->color = (node->color == RED) ? BLACK : RED;
    node->left->color = (node->left->color == RED) ? BLACK : RED;
    node->right->color = (node->right->color == RED) ? BLACK : RED;
}

// METODOS PUBLICOS

bool RBTree::search(int key) const
{
    return search(root, key);
};