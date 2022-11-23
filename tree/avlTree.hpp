#include <iostream>

#include "../node/avlTreeNode.hpp"

#ifndef AVL_TREE_H
#define AVL_TREE_H

class AVLTree
{
private:
    AVLTreeNode<int> *root = NULL;

    AVLTreeNode<int> *insert(AVLTreeNode<int> *root, int element);
    AVLTreeNode<int> *rotateRight(AVLTreeNode<int> *current);
    AVLTreeNode<int> *rotateLeft(AVLTreeNode<int> *current);

    void preorder(AVLTreeNode<int> *root);

    int height(AVLTreeNode<int> *root);

public:
    void insert(int element);
    void preorder();
};

AVLTreeNode<int> *AVLTree::rotateRight(AVLTreeNode<int> *current)
{
    AVLTreeNode<int>
        *curLeft = current->leftChild,
        *curLeftRight = curLeft->rightChild;

    curLeft->rightChild = current;
    current->leftChild = curLeftRight;

    if (root == current)
        root = curLeft;

    current->height = height(current);
    curLeft->height = height(curLeft);

    return curLeft;
}

AVLTreeNode<int> *AVLTree::rotateLeft(AVLTreeNode<int> *current)
{
    AVLTreeNode<int>
        *curRight = current->rightChild,
        *curRightLeft = curRight->leftChild;

    curRight->leftChild = current;
    current->rightChild = curRightLeft;

    current->height = height(current);
    curRight->height = height(curRight);

    if (root == current)
        root = curRight;

    return curRight;
}

AVLTreeNode<int> *AVLTree::insert(AVLTreeNode<int> *root, int element)
{
    if (!root)
        return new AVLTreeNode<int>(element);

    if (element < root->data)
        root->leftChild = insert(root->leftChild, element);
    else
        root->rightChild = insert(root->rightChild, element);

    root->height = height(root);

    int
        rootBF = root->balanceFactor(),
        leftChildBF = root->leftChild ? root->leftChild->balanceFactor() : 0,
        rightChildBF = root->rightChild ? root->rightChild->balanceFactor() : 0;

    if (rootBF == 2 && leftChildBF == 1)
        root = rotateRight(root);
    else if (rootBF == -2 && rightChildBF == -1)
        root = rotateLeft(root);
    else if (rootBF == 2 && leftChildBF == -1)
    {
        root->leftChild = rotateLeft(root->leftChild);
        root = rotateRight(root);
    }
    else if (rootBF == -2 && rightChildBF == 1)
    {
        root->rightChild = rotateRight(root->rightChild);
        root = rotateLeft(root);
    }

    return root;
}

void AVLTree::preorder(AVLTreeNode<int> *root)
{
    if (!root)
        return;

    cout << root;
    preorder(root->leftChild);
    preorder(root->rightChild);
}

int AVLTree::height(AVLTreeNode<int> *root)
{
    if (!root)
        return 0;

    int leftSubtreeHeight = root->leftChild ? root->leftChild->height : 0;
    int rightSubtreeHeight = root->rightChild ? root->rightChild->height : 0;
    return (leftSubtreeHeight > rightSubtreeHeight ? leftSubtreeHeight : rightSubtreeHeight) + 1;
}

void AVLTree::preorder()
{
    preorder(root);
    cout << "(NULL)\n";
}

void AVLTree::insert(int element)
{
    root = insert(root, element);
}

#endif