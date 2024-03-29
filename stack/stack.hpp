#include <iostream>

#include "../error/error.hpp"
#include "../node/node.hpp"

using namespace std;

#ifndef STACK_H
#define STACK_H

template <typename any>
class Stack
{
private:
    Node<any> *top = NULL;

public:
    Stack &push(any);

    any pop();
    any peek();

    void display();

    bool isEmpty();

    template <typename T>
    friend ostream &operator<<(ostream &, Stack<T> &);
};

template <typename any>
Stack<any> &Stack<any>::push(any element)
{
    Node<any> *temp = new Node<any>(element);

    temp->next = top;
    top = temp;

    return *this;
}

template <typename any>
any Stack<any>::pop()
{
    if (isEmpty())
        throw Error("underflow");

    Node<any> *temp = top;
    top = temp->next;
    any element = temp->data;
    delete temp;

    return element;
}

template <typename any>
any Stack<any>::peek()
{
    if (isEmpty())
        throw Error("underflow");

    return top->data;
}

template <typename any>
inline bool Stack<any>::isEmpty()
{
    return !top;
}

template <typename any>
void Stack<any>::display()
{
    for (Node<any> *traverser = top; traverser; traverser = traverser->next)
        cout << '[' << traverser->data << "]\n";

    cout << "[NULL]\n";
}

template <typename T>
ostream &operator<<(ostream &print, Stack<T> &s)
{
    s.display();
    return print;
}

#endif