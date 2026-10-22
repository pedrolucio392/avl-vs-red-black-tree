#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "RBNode.hpp"
#include <iostream>
#include <string>

class RBTree
{
private:
    RBNode *root;
    int rotationCount;

    // Métodos auxiliares
    bool isRed(RBNode *node) const;
    void flipColors(RBNode *node);
    void invertColor(RBNode *node);
    RBNode *moveRedLeft(RBNode *node);
    RBNode *moveRedRight(RBNode *node);
    RBNode *getMinimum(RBNode *node) const;
    RBNode *balance(RBNode *node);

    // Métodos de rotação
    RBNode *rotateLeft(RBNode *node);
    RBNode *rotateRight(RBNode *node);

    // Versões recursivas
    bool search(RBNode *node, int key) const;
    RBNode *insert(RBNode *node, int key);
    RBNode *remove(RBNode *node, int key);
    void printTree(RBNode *node, const std::string &prefix, bool isLeft) const;
    void destroyTree(RBNode *node);

public:
    RBTree();
    ~RBTree();

    void insert(int key);
    bool search(int key) const;
    void remove(int key);
    void printTree() const;

    int getRotationCount() const;
    RBNode *getRoot() const;
};

#endif