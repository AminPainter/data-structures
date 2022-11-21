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
    Node<any> *head = NULL;

public:
    SinglyList();
    SinglyList(any array[], int arraySize);
    SinglyList(const SinglyList &list);

    int length();
    int indexOf(any element);

    SinglyList &append(any element);
    SinglyList &prepend(any element);
    SinglyList &insert(any element, int index) throw(Error);
    SinglyList filter(bool (*)(any element, int index));

    any removeAt(int index = 0) throw(Error);
    any remove(any element) throw(Error);

    void clear();
    void reverse();
    void display();
    void forEach(void (*)(any element, int index));

    bool includes(any element);

    template <typename T>
    friend ostream &operator<<(ostream &, SinglyList<T> &);
};

template <typename any>
SinglyList<any>::SinglyList() {}

template <typename any>
SinglyList<any>::SinglyList(any array[], int arraySize)
{
    for (int i = 0; i < arraySize; i++)
        this->append(array[i]);
}

template <typename any>
SinglyList<any>::SinglyList(const SinglyList &list)
{
    for (Node<any> *traverser = list.head; traverser; traverser = traverser->next)
        this->append(traverser->data);
}

template <typename any>
SinglyList<any> &SinglyList<any>::append(any element)
{
    if (!head)
        return prepend(element);

    Node<any> *temp = new Node<any>(element), *traverser = head;
    while (traverser->next)
        traverser = traverser->next;

    traverser->next = temp;

    return *this;
}

template <typename any>
SinglyList<any> &SinglyList<any>::prepend(any element)
{
    Node<any> *temp = new Node<any>(element);
    temp->next = head;
    head = temp;

    return *this;
}

template <typename any>
SinglyList<any> &SinglyList<any>::insert(any element, int index) throw(Error)
{
    if (index < 0 || index >= length())
        throw Error("invalid index");

    Node<any> *temp = new Node<any>(element), *traverser = head;
    for (int i = 0; i < index - 1; i++)
        traverser = traverser->next;

    temp->next = traverser->next;
    traverser->next = temp;

    return *this;
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
        any element = temp->data;
        delete temp;

        return element;
    }

    Node<any> *traverser = head, *nodeToBeRemoved;
    for (int i = 0; i < index - 1; i++)
        traverser = traverser->next;

    nodeToBeRemoved = traverser->next;
    traverser->next = nodeToBeRemoved->next;
    any element = nodeToBeRemoved->data;
    delete nodeToBeRemoved;

    return element;
}

template <typename any>
any SinglyList<any>::remove(any element) throw(Error)
{
    if (head->data == element)
    {
        Node<any> *temp = head;
        head = temp->next;
        any element = temp->data;
        delete temp;

        return element;
    }

    for (Node<any> *traverser = head; traverser->next; traverser = traverser->next)
    {
        if (traverser->next->data != element)
            continue;

        Node<any> *nodeToBeRemoved = traverser->next;
        traverser->next = nodeToBeRemoved->next;
        any element = nodeToBeRemoved->data;
        delete nodeToBeRemoved;

        return element;
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
int SinglyList<any>::indexOf(any element)
{
    int i = 0;
    for (Node<any> *traverser = head; traverser; traverser = traverser->next, i++)
        if (traverser->data == element)
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
void SinglyList<any>::forEach(void (*fn)(any, int))
{
    int i = 0;
    for (Node<any> *traverser = head; traverser; traverser = traverser->next, i++)
        fn(traverser->data, i);
}

template <typename any>
bool SinglyList<any>::includes(any element)
{
    return indexOf(element) != -1;
}

template <typename T>
ostream &operator<<(ostream &print, SinglyList<T> &linkedList)
{
    linkedList.display();
    return print;
}

#endif