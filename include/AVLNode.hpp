#ifndef AVLNODE_HPP
#define AVLNODE_HPP

class AVLNode
{
public:
    int key;
    int height;
    AVLNode *left;
    AVLNode *right;

    AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    ~AVLNode() = default;
};

#endif