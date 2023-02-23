#include <iostream>

#include "../error/error.hpp"

using namespace std;

#ifndef ARRAY_H
#define ARRAY_H

template <typename any>
class Array
{
protected:
    any *arr;
    int len = 0, capacity;

    bool isValidIndex(int index);
    void resizeArrayAppropriately();

public:
    Array(int capacity = 10);
    Array(int *carray, int size);

    Array &insert(any element, int index = 0);
    Array &push(any element);

    void sort();

    int length();

    any operator[](int index);

    template <typename T>
    friend ostream &operator<<(ostream &print, Array<T> obj);
};

template <typename any>
Array<any>::Array(int capacity)
{
    this->capacity = capacity;
    this->arr = new int[capacity];
}

template <typename any>
Array<any>::Array(int *carray, int size)
{
    this->capacity = size * 2;
    this->arr = new int[this->capacity];

    for (int i = 0; i < size; i++)
        arr[i] = carray[i];

    len = size;
}

template <typename any>
bool Array<any>::isValidIndex(int index)
{
    return index >= 0 && index < len;
}

template <typename any>
int Array<any>::length()
{
    return len;
}

template <typename any>
void Array<any>::resizeArrayAppropriately()
{
    if (len + 1 < capacity)
        return;

    capacity *= 2;

    int *tempArr = new int[capacity];
    for (int i = 0; i < len; i++)
        tempArr[i] = arr[i];
    delete arr;
    arr = tempArr;
}

template <typename any>
Array<any> &Array<any>::push(any element)
{
    resizeArrayAppropriately();
    arr[len++] = element;
    return *this;
}

template <typename any>
Array<any> &Array<any>::insert(any element, int index)
{
    if (index < 0)
        index = len + index;

    if (index == len)
        return push(element);

    if (!isValidIndex(index))
        throw Error("Invalid index provided");

    resizeArrayAppropriately();

    for (int i = len - 1; i >= index; i--)
        arr[i + 1] = arr[i];

    arr[index] = element;
    len++;

    return *this;
}

template <typename any>
void Array<any>::sort()
{
    for (int i = 1; i < len; i++)
    {
        int key = arr[i];

        int j = i - 1;
        while (j > -1 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

template <typename any>
any Array<any>::operator[](int index)
{
    if (!isValidIndex(index))
        throw Error("Invalid index provided");

    return arr[index];
}

template <typename T>
ostream &operator<<(ostream &print, Array<T> obj)
{
    if (!obj.len)
        return print << "[NULL]";

    print << '[';

    int i;
    for (i = 0; i < obj.len - 1; i++)
        print << obj.arr[i] << ", ";

    print << obj.arr[i] << "]\n";
    return print;
}

#endif