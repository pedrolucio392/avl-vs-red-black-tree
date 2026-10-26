#ifndef RBNODE_HPP
#define RBNODE_HPP

#include <iostream>

enum Colors
{
    RED = true,
    BLACK
};

class RBNode
{
public:
    int key;
    Colors color;
    RBNode *left;
    RBNode *right;
    RBNode *parent;

    RBNode(int k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    ~RBNode() {}
};

#endif
