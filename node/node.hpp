#ifndef NODE_H
#define NODE_H

template <typename any>
struct Node
{
    any data;
    Node *next;

    Node() {}

    Node(any data, Node *next = __null)
    {
        this->data = data;
        this->next = next;
    }
};

#endif