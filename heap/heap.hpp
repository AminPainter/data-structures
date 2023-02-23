#include <iostream>
#include "../array/array.hpp"

using namespace std;

#ifndef HEAP_H
#define HEAP_H
#define FIRST_INDEX 1

class Heap : Array<int>
{
    static void swap(int &a, int &b);

public:
    Heap();

    Heap &insert(int element);
    void display();
    int remove();

    static Array heapSort(Array unsortedArray);
};

Array<int> Heap::heapSort(Array<int> unsortedArray)
{
    Heap tempHeap;
    for (int i = 0; i < unsortedArray.length(); i++)
        tempHeap.insert(unsortedArray[i]);

    Array<int> tempArray;
    for (int i = 0; i < unsortedArray.length(); i++)
        tempArray.insert(tempHeap.remove());

    return tempArray;
}

void Heap::swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

Heap::Heap()
{
    push(INT32_MAX);
}

Heap &Heap::insert(int element)
{
    push(element);

    int i = len - 1;
    while (i >= 1)
    {
        int parentEl = arr[i / 2];

        if (element > parentEl)
            arr[i] = parentEl;
        else
            break;

        i /= 2;
    }

    arr[i] = element;

    return *this;
}

void Heap::display()
{
    if (len <= 1)
    {
        cout << "[NULL]";
        return;
    }

    cout << '[';

    int i;
    for (i = 1; i < len - 1; i++)
        cout << arr[i] << ", ";

    cout << arr[i] << "]\n";
}

int Heap::remove()
{
    const int deletedElement = arr[FIRST_INDEX];

    swap(arr[FIRST_INDEX], arr[len - 1]);
    len--;

    int i = FIRST_INDEX;
    while (i < len)
    {
        int j = i * 2;
        if (!isValidIndex(j))
            break;
        if (isValidIndex(j + 1) && arr[j + 1] > arr[j])
            j++;

        if (arr[j] > arr[i])
            swap(arr[i], arr[j]);
        else
            break;

        i = j;
    }

    return deletedElement;
}

#endif