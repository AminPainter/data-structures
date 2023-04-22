#include <iostream>

#include "../error/error.hpp"
#include "../queue/queue.hpp"

using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
    int **graph;
    int size;

    void dfsTraversal(int startingVertex, int visited[]);

public:
    Graph(int size = 5);
    Graph(int **g, int size);

    void displayAdjacencyMatrix();
    void dfsTraversal(int startingVertex);
    void bfsTraversal(int startingVertex);

    Graph &addEdge(int startingVertex, int endingVertex);
};

Graph::Graph(int size)
{
    this->size = size;
    this->graph = new int *[size];

    for (int i = 1; i < size; i++)
        graph[i] = new int[size]();
}

Graph::Graph(int **g, int size) : Graph(size)
{
    for (int i = 1; i < size; i++)
        for (int j = 1; j < size; j++)
            graph[i][j] = g[i][j];
}

void Graph::displayAdjacencyMatrix()
{
    for (int i = 1; i < size; i++)
    {
        for (int j = 1; j < size; j++)
            cout << graph[i][j] << '\t';

        cout << "\n\n";
    }
}

Graph &Graph::addEdge(int startingVertex, int endingVertex)
{
    graph[startingVertex][endingVertex] = 1;
    return *this;
}

void Graph::dfsTraversal(int startingVertex, int visited[])
{
    cout << startingVertex << '\t';
    visited[startingVertex] = 1;

    for (int i = 1; i < size; i++)
        if (graph[startingVertex][i] && !visited[i])
            dfsTraversal(i, visited);
}

void Graph::dfsTraversal(int startingVertex)
{
    if (startingVertex >= size)
        throw Error("Invalid vertex");

    int visited[size] = {0};
    cout << "(\t";
    dfsTraversal(startingVertex, visited);
    cout << ")\n";
}

void Graph::bfsTraversal(int startingVertex)
{
    Queue<int> q;
    int visited[size] = {0};
    q.enqueue(startingVertex);
    cout << startingVertex << '\t';
    visited[startingVertex] = 1;

    while (!q.isEmpty())
    {
        int explorer = q.dequeue();

        for (int i = 1; i < size; i++)
        {
            if (graph[explorer][i] && !visited[i])
            {
                q.enqueue(i);
                cout << i << '\t';
                visited[i] = 1;
            }
        }
    }

    cout << '\n';
}

#endif