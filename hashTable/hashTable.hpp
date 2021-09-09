/////////////////////////////////////
// Hash Table

#include <iostream>

#include "../linkedList/singly.hpp"
#include "../error/error.hpp"

using namespace std;

class HashTable
{
private:
    // Class variables
    static const int SIZE = 10;

    // Instance variables
    SinglyList<int> table[SIZE];

    // Private methods
    int hash(int);

public:
    HashTable &insert(int);

    int *search(int);

    int remove(int) throw(Error);
    int removeAt(int *) throw(Error);

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

int HashTable::remove(int key) throw(Error)
{
    return table[hash(key)].remove(key);
}

int HashTable::removeAt(int *coords) throw(Error)
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