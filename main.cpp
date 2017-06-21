#include <iostream>
#include "Graph.h"

using namespace std;

template<class T>
int Node<T>::number = 0;

int main() {
    Graph<int> *graph = new Graph<int>();

    Node<int> *node1 = new Node<int>(0);
    Node<int> *node2 = new Node<int>(1);
    Node<int> *node3 = new Node<int>(2);
    Node<int> *node4 = new Node<int>(3);
    Node<int> *node5 = new Node<int>(4);
    Node<int> *node6 = new Node<int>(5);

    Edge<int> *edge1 = new Edge<int>(node1, node2, 0);
    Edge<int> *edge2 = new Edge<int>(node2, node3, 1);
    Edge<int> *edge3 = new Edge<int>(node3, node1, 2);
    Edge<int> *edge4 = new Edge<int>(node1, node4, 3);
    Edge<int> *edge5 = new Edge<int>(node1, node5, 4);
    Edge<int> *edge6 = new Edge<int>(node5, node6, 5);

    graph->addEdge(edge1);
    graph->addEdge(edge2);
    graph->addEdge(edge3);
    graph->addEdge(edge4);
    graph->addEdge(edge5);
    graph->addEdge(edge6);


    auto tree = graph->BFS(0);

    return 0;
}