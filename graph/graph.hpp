#include <iostream>

#include "../error/error.hpp"
#include "../queue/queue.hpp"

using namespace std;

#ifndef GRAPH_H
#define GRAPH_H
#define INFINITY INT32_MAX

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
    void getSpanningTreeByPrims();

    Graph &addEdge(int startingVertex, int endingVertex, int weight = 1);
};

Graph::Graph(int size)
{
    this->size = size;
    this->graph = new int *[size];

    for (int i = 1; i < size; i++)
        graph[i] = new int[size]();

    for (int i = 1; i < size; i++)
        for (int j = 1; j < size; j++)
            graph[i][j] = INFINITY;
}

Graph::Graph(int **g, int size) : Graph(size)
{
    for (int i = 1; i < size; i++)
        for (int j = 1; j < size; j++)
            graph[i][j] = g[i][j] == 0 ? INFINITY : g[i][j];
}

void Graph::displayAdjacencyMatrix()
{
    for (int i = 1; i < size; i++)
    {
        for (int j = 1; j < size; j++)
        {
            if (graph[i][j] == INFINITY)
                cout << "-\t";
            else
                cout << graph[i][j] << '\t';
        }
        cout << "\n\n";
    }
}

Graph &Graph::addEdge(int startingVertex, int endingVertex, int weight)
{
    graph[startingVertex][endingVertex] = weight;
    return *this;
}

void Graph::dfsTraversal(int startingVertex, int visited[])
{
    cout << startingVertex << '\t';
    visited[startingVertex] = 1;

    for (int i = 1; i < size; i++)
        if (graph[startingVertex][i] != INFINITY && !visited[i])
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
            if (graph[explorer][i] != INFINITY && !visited[i])
            {
                q.enqueue(i);
                cout << i << '\t';
                visited[i] = 1;
            }
        }
    }

    cout << '\n';
}

void Graph::getSpanningTreeByPrims()
{
    int min = INFINITY, v1, v2;
    int spanningTree[2][size - 1] = {0};

    int near[size];
    for (int i = 0; i < size; i++)
        near[i] = INFINITY;

    // Find edge with least cost
    for (int i = 1; i < size; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (graph[i][j] < min)
            {
                min = graph[i][j];
                v2 = i;
                v1 = j;
            }
        }
    }

    // Insert that edge in spanning tree
    spanningTree[0][0] = v1;
    spanningTree[1][0] = v2;

    // Include the first set of vertices
    near[v1] = near[v2] = 0;

    // Update near array
    for (int i = 1; i < size; i++)
    {
        if (near[i] == 0)
            continue;

        if (graph[i][v1] < graph[i][v2])
            near[i] = v1;
        else
            near[i] = v2;
    }

    // Repeating steps
    int k;
    for (int i = 1; i < size - 1; i++)
    {
        min = INFINITY;

        // Find next minimum cost edge connected with previous vertices
        for (int j = 1; j < size; j++)
        {
            if (near[j] != 0 && graph[j][near[j]] < min)
            {
                min = graph[j][near[j]];
                k = j;
            }
        }

        spanningTree[0][i] = k;
        spanningTree[1][i] = near[k];

        // Include the next minimum edge vertices in near array
        near[k] = 0;

        // Update near array
        for (int j = 1; j < size; j++)
            if (near[j] != 0 && graph[j][k] < graph[j][near[j]])
                near[j] = k;
    }

    // Print final spanning tree
    for (int i = 0; i < size - 2; i++)
        cout << '(' << spanningTree[0][i] << ", " << spanningTree[1][i] << ")\n";
}

#endif