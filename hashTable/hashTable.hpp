#include <iostream>

#include "../linkedList/singly.hpp"
#include "../error/error.hpp"

using namespace std;

#ifndef HASHTABLE_H
#define HASHTABLE_H

class HashTable
{
private:
    static const int SIZE = 10;
    SinglyList<int> table[SIZE];

    int hash(int);

public:
    HashTable &insert(int);

    int *search(int);

    int remove(int);
    int removeAt(int *);

    void clear();
    void display();

    friend ostream &operator<<(ostream &, HashTable &);
};
const int HashTable::SIZE;

int HashTable::hash(int key)
{
    return key % SIZE;
}

HashTable &HashTable::insert(int key)
{
    table[hash(key)].prepend(key);
    return *this;
}

int *HashTable::search(int key)
{
    int *coords = new int[2];
    coords[0] = hash(key);
    coords[1] = table[coords[0]].indexOf(key);

    if (coords[1] == -1)
        coords[0] = coords[1];

    return coords;
}

int HashTable::remove(int key)
{
    return table[hash(key)].remove(key);
}

int HashTable::removeAt(int *coords)
{
    if (coords[0] < 0 || coords[0] >= SIZE)
        throw Error("invalid index");

    return table[coords[0]].removeAt(coords[1]);
}

void HashTable::clear()
{
    for (SinglyList<int> &currentList : table)
        currentList.clear();
}

void HashTable::display()
{
    for (int i = 0; i < SIZE; i++)
        cout << i << " => " << table[i];
}

ostream &operator<<(ostream &print, HashTable &ht)
{
    ht.display();
    return print;
}

#endif