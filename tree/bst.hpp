#include <iostream>

#include "../node/treeNode.hpp"
#include "../error/error.hpp"
#include "../stack/stack.hpp"
#include "./binaryTree.hpp"

using namespace std;

#ifndef BST_H
#define BST_H

class BST : public BinaryTree
{
private:
    TreeNode<int> *remove(TreeNode<int> *current, int element);
    TreeNode<int> *inorderSuccessor(TreeNode<int> *p);
    TreeNode<int> *inorderPredecessor(TreeNode<int> *p);

public:
    static BST fromPreorder(int preorder[], int preorderLength);

    void insert(int element);

    TreeNode<int> *search(int key);
    TreeNode<int> *remove(int element);

    bool includes(int key);
};

TreeNode<int> *BST::inorderSuccessor(TreeNode<int> *p)
{
    if (!p)
        return NULL;

    TreeNode<int> *successor = p->rightChild;
    while (successor->leftChild)
        successor = successor->leftChild;

    return successor;
}

TreeNode<int> *BST::inorderPredecessor(TreeNode<int> *p)
{
    if (!p)
        return NULL;

    TreeNode<int> *predecessor = p->leftChild;
    while (predecessor->rightChild)
        predecessor = predecessor->rightChild;

    return predecessor;
}

TreeNode<int> *BST::remove(int element)
{
    return remove(root, element);
}

TreeNode<int> *BST::remove(TreeNode<int> *current, int element)
{
    // Tree is empty
    // Element could not be located
    // NULL should be stored in the parent whose child just got deleted
    if (!current)
        return NULL;

    // Search for the element in the left sub tree
    if (element < current->data)
    {
        // All changes done in the left subtree should be stored back in left subtree
        current->leftChild = remove(current->leftChild, element);
        return current;
    }

    // Search for the element in the right sub tree
    if (element > current->data)
    {
        // All changes done in the right subtree should be stored back in right subtree
        current->rightChild = remove(current->rightChild, element);
        return current;
    }

    // CASE 1: Found element is a leaf node
    if (current->isLeafNode())
    {
        // Check if root was deleted, root will only be leaf if there is a single node in the tree
        if (current == root)
            root = NULL;
        // Physical node deletion from memory always happen on leaf nodes
        delete current;
        return NULL;
    }

    // CASE 2: Found element is a non-leaf node
    // Delete a leaf node from right subtree if right subtree is larger than left subtree
    if (height(current->rightChild) > height(current->leftChild))
    {
        // Find inorder successor of current node (p)
        TreeNode<int> *successor = inorderSuccessor(current);
        // Replace current node's data with successor
        current->data = successor->data;
        // A successor can also have some child nodes, so delete successor the same way as you deleted current node
        current->rightChild = remove(current->rightChild, successor->data);
    }
    // Delete a leaf node from left subtree if left subtree is larger than right subtree
    else
    {
        // Find inorder predecessor of current node (p)
        TreeNode<int> *predecessor = inorderPredecessor(current);
        // Replace current node's data with predecessor
        current->data = predecessor->data;
        // A predecessor can also have some child nodes, so delete predecessor the same way as you deleted current node
        current->leftChild = remove(current->leftChild, predecessor->data);
    }
    return current;
}

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