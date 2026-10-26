#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "AVLNode.hpp"

#include <iostream>
#include <string>

class AVLTree
{
private:
    AVLNode *root;
    int rotationCount;

    // Métodos auxiliares
    int height(AVLNode *node) const;
    int getBalance(AVLNode *node) const;
    void updateHeight(AVLNode *node);

    // Métodos de rotação
    AVLNode *rotateRight(AVLNode *y);
    AVLNode *rotateLeft(AVLNode *x);

    // Metodos principais
    AVLNode *insert(AVLNode *node, int key);
    AVLNode *remove(AVLNode *node, int key);
    AVLNode *getMin(AVLNode *node) const;

    void destroyAVL(AVLNode *node);
    bool search(AVLNode *node, int key) const;
    void printInOrder(AVLNode *node) const;
    void printTree(AVLNode *node, const std::string &prefix, bool isLeft) const;

public:
    AVLTree();
    ~AVLTree();

    // Métodos principais
    void insert(int key);
    void remove(int key);
    bool search(int key) const;

    // Auxiliares
    void clear();
    int height() const;
    int getRotationCount() const;
    void resetRotationCount();
    void printInOrder() const;
    void printTree() const;
};

#endif