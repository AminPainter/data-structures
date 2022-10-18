#include <iostream>

#include "../node/treeNode.hpp"
#include "../error/error.hpp"
#include "../stack/stack.hpp"

using namespace std;

#ifndef BST_H
#define BST_H

class BST
{
private:
    TreeNode<int> *root = NULL;

    void inorder(TreeNode<int> *root);
    void preorder(TreeNode<int> *root);
    void postorder(TreeNode<int> *root);

public:
    static BST fromPreorder(int preorder[], int preorderLength);

    void insert(int element);
    void inorder();
    void preorder();
    void postorder();

    TreeNode<int> *search(int key);

    bool includes(int key);
};

BST BST::fromPreorder(int preorder[], int preorderLength)
{
    BST tree;
    if (!preorderLength)
        return tree;

    TreeNode<int> *traverser;
    Stack<TreeNode<int> *> collector;

    traverser = tree.root = new TreeNode<int>(preorder[0]);

    int i = 1;
    while (i < preorderLength)
    {
        int nextElement = preorder[i];
        TreeNode<int> *temp = new TreeNode<int>(nextElement);

        if (nextElement < traverser->data)
        {
            traverser->leftChild = temp;
            collector.push(traverser);
            traverser = traverser->leftChild;
            i++;
            continue;
        }

        if (collector.isEmpty() || nextElement < collector.peek()->data)
        {
            traverser->rightChild = temp;
            traverser = traverser->rightChild;
            i++;
            continue;
        }

        traverser = collector.pop();
    }

    return tree;
}

void BST::insert(int element)
{
    TreeNode<int> *temp = new TreeNode<int>(element);
    if (!root)
    {
        root = temp;
        return;
    }

    TreeNode<int> *traverser = root, *following;
    while (traverser)
    {
        following = traverser;
        if (traverser->data == element)
            throw new Error(element + " already exists");

        if (element < traverser->data)
            traverser = traverser->leftChild;
        else
            traverser = traverser->rightChild;
    }

    if (element < following->data)
        following->leftChild = temp;
    else
        following->rightChild = temp;
}

void BST::inorder(TreeNode<int> *root)
{
    if (!root)
        return;
    inorder(root->leftChild);
    cout << root;
    inorder(root->rightChild);
}

void BST::preorder(TreeNode<int> *root)
{
    if (!root)
        return;
    cout << root;
    preorder(root->leftChild);
    preorder(root->rightChild);
}

void BST::postorder(TreeNode<int> *root)
{
    if (!root)
        return;
    postorder(root->leftChild);
    postorder(root->rightChild);
    cout << root;
}

void BST::inorder()
{
    inorder(root);
    cout << '\n';
}

void BST::preorder()
{
    preorder(root);
    cout << '\n';
}

void BST::postorder()
{
    postorder(root);
    cout << '\n';
}

TreeNode<int> *BST::search(int key)
{
    TreeNode<int> *traverser = root;
    while (traverser)
    {
        if (key == traverser->data)
            return traverser;

        if (key < traverser->data)
            traverser = traverser->leftChild;
        else
            traverser = traverser->rightChild;
    }
    return NULL;
}

bool BST::includes(int key)
{
    return search(key) != NULL;
}

#endif