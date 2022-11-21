#include <iostream>

using namespace std;

#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H

template <typename any>
struct AVLTreeNode
{
    AVLTreeNode *leftChild = NULL, *rightChild = NULL;
    int height = 1;
    any data;

    AVLTreeNode() {}

    AVLTreeNode(any data)
    {
        this->data = data;
    }

    bool isLeafNode()
    {
        return !leftChild && !rightChild;
    }

    int balanceFactor()
    {
        int leftSubTreeHeight = leftChild ? leftChild->height : 0;
        int rightSubTreeHeight = rightChild ? rightChild->height : 0;
        return leftSubTreeHeight - rightSubTreeHeight;
    }

    template <typename T>
    friend ostream &operator<<(ostream &out, AVLTreeNode<T> *treeNode);
};

template <typename T>
ostream &operator<<(ostream &out, AVLTreeNode<T> *treeNode)
{
    out << '(' << treeNode->data << ")";
    return out;
}

#endif