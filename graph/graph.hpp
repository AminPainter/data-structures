#include <iostream>

#include "../error/error.hpp"

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
    if (startingVertex >= size)
        throw Error("Invalid vertex");

    cout << startingVertex << '\t';
    visited[startingVertex] = 1;

    for (int i = 1; i < size; i++)
        if (graph[startingVertex][i] && !visited[i])
            dfsTraversal(i, visited);
}

void Graph::dfsTraversal(int startingVertex)
{
    int visited[size] = {0};
    cout << "(\t";
    dfsTraversal(startingVertex, visited);
    cout << ")\n";
}

#endif