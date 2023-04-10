#include <iostream>

using namespace std;

#ifndef HEAP_H
#define HEAP_H
#define HEAP_START_INDEX 1

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

class Heap
{
    int *heap, length;

    void heapify(int currentNodeIndex);

    friend ostream &operator<<(ostream &print, Heap obj);

public:
    Heap(int *array, int n);

    int remove();

    static void heapSort(int *array, int n);
};

Heap::Heap(int *array, int n)
{
    this->length = n + 1;
    this->heap = new int[this->length];

    for (int i = 0; i < n; i++)
        this->heap[i + 1] = array[i];

    for (int i = length / 2; i >= HEAP_START_INDEX; i--)
        heapify(i);
}

void Heap::heapify(int currentNodeIndex)
{
    int
        leftChildIndex = currentNodeIndex * 2,
        rightChildIndex = leftChildIndex + 1,
        largestNodeIndex = currentNodeIndex;

    if (leftChildIndex < length && heap[leftChildIndex] > heap[largestNodeIndex])
        largestNodeIndex = leftChildIndex;

    if (rightChildIndex < length && heap[rightChildIndex] > heap[largestNodeIndex])
        largestNodeIndex = rightChildIndex;

    if (largestNodeIndex == currentNodeIndex)
        return;

    swap(heap[currentNodeIndex], heap[largestNodeIndex]);
    heapify(largestNodeIndex);
}

ostream &operator<<(ostream &print, Heap obj)
{
    for (int i = HEAP_START_INDEX; i < obj.length; i++)
        cout << '(' << obj.heap[i] << ')';

    cout << '\n';
}

int Heap::remove()
{
    int
        rootNodeIndex = HEAP_START_INDEX,
        removedElement = heap[rootNodeIndex],
        leftChildIndex, rightChildIndex, largestNodeIndex;

    swap(heap[rootNodeIndex], heap[length - 1]);
    length--;

    while (rootNodeIndex < length)
    {
        largestNodeIndex = rootNodeIndex;
        leftChildIndex = rootNodeIndex * 2;
        rightChildIndex = leftChildIndex + 1;

        if (leftChildIndex < length && heap[leftChildIndex] > heap[largestNodeIndex])
            largestNodeIndex = leftChildIndex;
        if (rightChildIndex < length && heap[rightChildIndex] > heap[largestNodeIndex])
            largestNodeIndex = rightChildIndex;

        if (largestNodeIndex == rootNodeIndex)
            break;

        swap(heap[largestNodeIndex], heap[rootNodeIndex]);
        rootNodeIndex = largestNodeIndex;
    }

    return removedElement;
}

void Heap::heapSort(int *array, int n)
{
    Heap tempHeap(array, n);

    for (int i = tempHeap.length - 1; i >= HEAP_START_INDEX; i--)
        tempHeap.heap[i] = tempHeap.remove();

    for (int i = 0; i < n; i++)
        array[i] = tempHeap.heap[i + 1];
}

#endif