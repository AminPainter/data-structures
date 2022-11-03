/////////////////////////////////////
// Queue

#include <iostream>

#include "../error/error.hpp"
#include "../node/node.hpp"

using namespace std;

#ifndef QUEUE_H
#define QUEUE_H

template <typename any>
class Queue
{
private:
    Node<any> *front = NULL, *rear = NULL;

public:
    Queue &enqueue(any);

    any dequeue() throw(Error);
    any peek() throw(Error);

    void display();

    bool isEmpty();

    template <typename T>
    friend ostream &operator<<(ostream &, Queue<T> &);
};

template <typename any>
Queue<any> &Queue<any>::enqueue(any data)
{
    Node<any> *temp = new Node<any>(data);

    if (isEmpty())
        front = rear = temp;
    else
    {
        rear->next = temp;
        rear = temp;
    }

    return *this;
}

template <typename any>
any Queue<any>::dequeue() throw(Error)
{
    if (isEmpty())
        throw Error("underflow");

    Node<any> *temp = front;
    front = temp->next;
    any data = temp->data;
    delete temp;

    if (!front)
        rear = NULL;

    return data;
}

template <typename any>
any Queue<any>::peek() throw(Error)
{
    if (isEmpty())
        throw Error("underflow");

    return front->data;
}

template <typename any>
inline bool Queue<any>::isEmpty()
{
    return !rear;
}

template <typename any>
void Queue<any>::display()
{
    for (Node<any> *traverser = front; traverser; traverser = traverser->next)
        cout << '[' << traverser->data << ']';

    cout << "[NULL]\n";
}

template <typename T>
ostream &operator<<(ostream &print, Queue<T> &q)
{
    q.display();
    return print;
}

#endif