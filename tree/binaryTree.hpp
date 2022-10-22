#include <iostream>

#include "../node/treeNode.hpp"

using namespace std;

#ifndef BINARYTREE_H
#define BINARYTREE_H

class BinaryTree
{
protected:
    TreeNode<int> *root = NULL;

    void inorder(TreeNode<int> *root);
    void preorder(TreeNode<int> *root);
    void postorder(TreeNode<int> *root);

    int count(TreeNode<int> *root);
    int countLeaves(TreeNode<int> *root);
    int height(TreeNode<int> *root);

public:
    void inorder();
    void preorder();
    void postorder();

    int count();
    int countLeaves();
    int height();

    friend ostream &operator<<(ostream &, BinaryTree &);
};

int BinaryTree::count(TreeNode<int> *root)
{
    return root ? count(root->leftChild) + count(root->rightChild) + 1 : 0;
}

int BinaryTree::count()
{
    return count(root);
}

int BinaryTree::countLeaves(TreeNode<int> *root)
{
    if (!root)
        return 0;

    int x = countLeaves(root->leftChild), y = countLeaves(root->rightChild);
    return root->isLeafNode() ? x + y + 1 : x + y;
}

int BinaryTree::countLeaves()
{
    return countLeaves(root);
}

int BinaryTree::height(TreeNode<int> *root)
{
    if (!root)
        return -1;

    int x = height(root->leftChild), y = height(root->rightChild);
    return (x > y ? x : y) + 1;
}

int BinaryTree::height()
{
    return height(root);
}

void BinaryTree::inorder(TreeNode<int> *root)
{
    if (!root)
        return;
    inorder(root->leftChild);
    cout << root;
    inorder(root->rightChild);
}

void BinaryTree::preorder(TreeNode<int> *root)
{
    if (!root)
        return;
    cout << root;
    preorder(root->leftChild);
    preorder(root->rightChild);
}

void BinaryTree::postorder(TreeNode<int> *root)
{
    if (!root)
        return;
    postorder(root->leftChild);
    postorder(root->rightChild);
    cout << root;
}

void BinaryTree::inorder()
{
    inorder(root);
    cout << '\n';
}

void BinaryTree::preorder()
{
    preorder(root);
    cout << '\n';
}

void BinaryTree::postorder()
{
    postorder(root);
    cout << '\n';
}

ostream &operator<<(ostream &print, BinaryTree &tree)
{
    tree.inorder();
}

#endif
