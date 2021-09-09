/////////////////////////////////////
// Singly Linked List

#include <iostream>

#include "../error/error.hpp"
#include "../node/node.hpp"

using namespace std;

#ifndef SINGLY_H
#define SINGLY_H

template <typename any>
class SinglyList
{
protected:
    Node<any> *head;

public:
    SinglyList();
    SinglyList(const SinglyList &);

    int length();
    int indexOf(any);

    SinglyList &append(any);
    SinglyList &prepend(any);
    SinglyList &insert(any, int) throw(Error);
    SinglyList filter(bool (*)(any));
    SinglyList filter(bool (*)(any, int));

    any removeAt(int = 0) throw(Error);
    any remove(int) throw(Error);

    void clear();
    void reverse();
    void display();
    void forEach(void (*)(any));
    void forEach(void (*)(any, int));

    bool includes(any);

    template <typename T>
    friend ostream &operator<<(ostream &, SinglyList<T> &);
};

template <typename any>
SinglyList<any>::SinglyList()
{
    this->head = NULL;
}

template <typename any>
SinglyList<any>::SinglyList(const SinglyList &list)
{
    this->head = NULL;

    for (Node<any> *traverser = list.head; traverser; traverser = traverser->next)
        this->append(traverser->data);
}

template <typename any>
SinglyList<any> &SinglyList<any>::append(any data)
{
    if (!head)
        return prepend(data);

    Node<any> *temp = new Node<any>(data), *traverser = head;
    while (traverser->next)
        traverser = traverser->next;

    traverser->next = temp;

    return *this;
}

template <typename any>
SinglyList<any> &SinglyList<any>::prepend(any data)
{
    Node<any> *temp = new Node<any>(data);
    temp->next = head;
    head = temp;

    return *this;
}

template <typename any>
SinglyList<any> &SinglyList<any>::insert(any data, int index) throw(Error)
{
    if (index < 0 || index >= length())
        throw Error("invalid index");

    Node<any> *temp = new Node<any>(data), *traverser = head;
    for (int i = 0; i < index - 1; i++)
        traverser = traverser->next;

    temp->next = traverser->next;
    traverser->next = temp;

    return *this;
}

template <typename any>
SinglyList<any> SinglyList<any>::filter(bool (*fn)(any))
{
    SinglyList<any> temporary;

    for (Node<any> *traverser = head; traverser; traverser = traverser->next)
        if (fn(traverser->data))
            temporary.append(traverser->data);

    return temporary;
}

template <typename any>
SinglyList<any> SinglyList<any>::filter(bool (*fn)(any, int))
{
    SinglyList<any> temporary;

    int i = 0;
    for (Node<any> *traverser = head; traverser; traverser = traverser->next, i++)
        if (fn(traverser->data, i))
            temporary.append(traverser->data);

    return temporary;
}

template <typename any>
any SinglyList<any>::removeAt(int index) throw(Error)
{
    if (index < 0 || index >= length())
        throw Error("invalid index");

    if (!index)
    {
        Node<any> *temp = head;
        head = temp->next;
        any data = temp->data;
        delete temp;

        return data;
    }

    Node<any> *traverser = head, *nodeToBeRemoved;
    for (int i = 0; i < index - 1; i++)
        traverser = traverser->next;

    nodeToBeRemoved = traverser->next;
    traverser->next = nodeToBeRemoved->next;
    any data = nodeToBeRemoved->data;
    delete nodeToBeRemoved;

    return data;
}

template <typename any>
any SinglyList<any>::remove(int key) throw(Error)
{
    if (head->data == key)
    {
        Node<any> *temp = head;
        head = temp->next;
        any data = temp->data;
        delete temp;

        return data;
    }

    for (Node<any> *traverser = head; traverser->next; traverser = traverser->next)
    {
        if (traverser->next->data != key)
            continue;

        Node<any> *nodeToBeRemoved = traverser->next;
        traverser->next = nodeToBeRemoved->next;
        any data = nodeToBeRemoved->data;
        delete nodeToBeRemoved;

        return data;
    }

    throw Error("element does not exist");
}

template <typename any>
int SinglyList<any>::length()
{
    int len = 0;
    for (Node<any> *traverser = head; traverser; traverser = traverser->next)
        len++;

    return len;
}

template <typename any>
int SinglyList<any>::indexOf(any data)
{
    int i = 0;
    for (Node<any> *traverser = head; traverser; traverser = traverser->next, i++)
        if (traverser->data == data)
            return i;

    return -1;
}

template <typename any>
void SinglyList<any>::clear()
{
    Node<any> *current = head, *next = NULL;

    while (current)
    {
        next = current->next;
        delete current;
        current = next;
    }

    head = NULL;
}

template <typename any>
void SinglyList<any>::reverse()
{
    Node<any> *previous = NULL, *current = head, *following;

    while (current)
    {
        following = current->next;
        current->next = previous;

        previous = current;
        current = following;
    }

    head = previous;
}

template <typename any>
void SinglyList<any>::display()
{
    for (Node<any> *traverser = head; traverser; traverser = traverser->next)
        cout << '[' << traverser->data << "]-->";

    cout << "[NULL]\n";
}

template <typename any>
void SinglyList<any>::forEach(void (*fn)(any))
{
    for (Node<any> *traverser = head; traverser; traverser = traverser->next)
        fn(traverser->data);
}

template <typename any>
void SinglyList<any>::forEach(void (*fn)(any, int))
{
    int i = 0;
    for (Node<any> *traverser = head; traverser; traverser = traverser->next, i++)
        fn(traverser->data, i);
}

template <typename any>
bool SinglyList<any>::includes(any data)
{
    return indexOf(data) != -1;
}

template <typename T>
ostream &operator<<(ostream &print, SinglyList<T> &linkedList)
{
    linkedList.display();
    return print;
}

#endif