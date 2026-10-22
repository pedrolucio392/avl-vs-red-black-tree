#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "AVLNode.hpp"

#include <iostream>
#include <string>

class AVLTree
{
private:
    AVLNode *root;
    int rotationCount = 0;

    // Métodos auxiliares
    int getNodeHeight(AVLNode *node) const;
    int getBalanceFactor(AVLNode *node) const;
    void updateHeight(AVLNode *node);
    AVLNode *getMinValueNode(AVLNode *node);
    void inOrder(AVLNode *node) const;

    // Rotações
    AVLNode *rotateRight(AVLNode *y);
    AVLNode *rotateLeft(AVLNode *x);

    // Versões recursivas
    bool search(AVLNode *node, int key) const;
    AVLNode *insert(AVLNode *node, int key);
    AVLNode *remove(AVLNode *node, int key);
    void printTree(AVLNode *node, const std::string &prefix, bool isLeft) const;
    void destroyTree(AVLNode *node);

public:
    AVLTree();
    ~AVLTree();

    void insert(int key);
    void remove(int key);
    bool search(int key) const;
    void printTree() const;
    void inOrder() const;

    int getTreeHeight() const;
    int getRotationCount() const;
    AVLNode *getRoot() const;
    int max(int a, int b);
};

#endif