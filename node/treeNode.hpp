/////////////////////////////////////
// Tree Node

#include <iostream>

using namespace std;

#ifndef TREE_NODE_H
#define TREE_NODE_H

template <typename any>
struct TreeNode
{
    TreeNode *leftChild = NULL, *rightChild = NULL;
    any data;

    TreeNode() {}

    TreeNode(any data)
    {
        this->data = data;
    }

    template <typename T>
    friend ostream &operator<<(ostream &out, TreeNode<T> *treeNode);
};

template <typename T>
ostream &operator<<(ostream &out, TreeNode<T> *treeNode)
{
    out << '(' << treeNode->data << ")";
    return out;
}

#endif