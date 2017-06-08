//
// Created by Thoxvi on 2017/6/8.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H


#include <vector>

template<class T>
class Node {
private:
    int ID;
    T *data;
public:
    static int number;

    Node(T d) : data(new T(d)), ID(number++) {}

    bool same(Node &d) {
        return ID == d.getID();
    }

    //Setter && Getter
    T *getData() const {
        return data;
    }

    void setData(T *data) {
        Node::data = data;
    }

    int getID() const {
        return ID;
    }
};


template<class T>
class Edge {
private:
    Node<T> *start;
    Node<T> *end;
    int power;      //-1为单点
public:
    Edge(Node<T> *s, Node<T> *e, int p) : start(s), end(e), power(p) {}

    Edge(Node<T> *s) : start(s), end(nullptr), power(-1) {}

    bool isSinglNode() { return power == -1; }

    bool isStart(Node<T> &node) {
        return start->same(node);
    }

    bool isEnd(Node<T> &node) {
        return end->same(node);
    }

    bool isMyNode(Node<T> &node) {
        return isStart(node) || isEnd(node);
    }

    //Setter && Getter
    Node<T> *getStart() {
        return start;
    }

    void setStart(Node<T> *start) {
        Edge::start = start;
    }

    Node<T> *getEnd() {
        return end;
    }

    void setEnd(Node<T> *end) {
        Edge::end = end;
    }
};

template<class T>
class Graph {
private:
    std::vector<Edge<T> *> edges;

    void DFSHelper(Graph *tree, std::vector<Edge<T> *> &restEdge, std::vector<Node<T> *> &visitedNode);

    bool isNodeInList(Node<T> *node, std::vector<Node<T> *> &list) {
        auto it = std::find(list.begin(), list.end(), node);
        return !(it == list.end());
    }

public:
    Graph() {};

    void addNode(T data);

    void addNode(Node<T> *node);

    void addEdge(T start, T end, int power);

    void addEdge(Node<T> *start, Node<T> *end, int power);

    void addEdge(Edge<T> *edge);

    std::vector<Node<T> *> getAllNodeFromEdges();

    std::vector<Edge<T> *> getEdgeIfNodeIn(int ID);

    std::vector<Edge<T> *> getEdgeIfNodeStart(int ID);

    std::vector<Edge<T> *> getEdgeIfNodeEnd(int ID);

    Node<T> *getNodeByID(int ID);

    bool hasEdge(int sID, int eID);

    bool delEdge(int sID, int eID);

    //深度优先遍历
    Graph<T> *DFS(int sID);

    //深度优先遍历B
    Graph<T> *BFS(int sID);

};

template<class T>
void Graph<T>::addNode(T data) {
    edges.push_back(new Edge<T>(new Node<T>(data)));
}

template<class T>
void Graph<T>::addNode(Node<T> *node) {
    edges.push_back(new Edge<T>(node));
}

template<class T>
void Graph<T>::addEdge(T start, T end, int power) {
    edges.push_back(new Edge<T>(new Node<T>(start), new Node<T>(end), power));
}

template<class T>
void Graph<T>::addEdge(Node<T> *start, Node<T> *end, int power) {
    edges.push_back(new Edge<T>(start, end, power));

}

template<class T>
void Graph<T>::addEdge(Edge<T> *edge) {
    edges.push_back(edge);
}

template<class T>
std::vector<Node<T> *> Graph<T>::getAllNodeFromEdges() {
    std::vector<Node<T> *> nodeList;
    for (Edge<T> *edge:edges) {
        if (edge->isSinglNode()) {
            nodeList.push_back(edge->getStart());
        } else {
            Node<T> *node = edge->getStart();
            if (!isNodeInList(node, nodeList)) {
                nodeList.push_back(node);
            }
        }
    }
    return nodeList;
}

template<class T>
std::vector<Edge<T> *> Graph<T>::getEdgeIfNodeIn(int ID) {
    std::vector<Edge<T> *> list;
    for (Edge<T> *edge:edges) {
        if (edge->getStart()->getID() == ID ||
            edge->getEnd()->getID() == ID) {
            list.push_back(edge);
        }
    }
    return list;
}

template<class T>
std::vector<Edge<T> *> Graph<T>::getEdgeIfNodeStart(int ID) {
    std::vector<Edge<T> *> list;
    for (Edge<T> *edge:edges) {
        if (edge->getStart()->getID() == ID) {
            list.push_back(edge);
        }
    }
    return list;
}

template<class T>
std::vector<Edge<T> *> Graph<T>::getEdgeIfNodeEnd(int ID) {
    std::vector<Edge<T> *> list;
    for (Edge<T> *edge:edges) {
        if (edge->getEnd()->getID() == ID) {
            list.push_back(edge);
        }
    }
    return list;
}

template<class T>
Node<T> *Graph<T>::getNodeByID(int ID) {
    for (Node<T> *node:getAllNodeFromEdges()) {
        if (node->getID() == ID) {
            return node;
        }
    }
    return nullptr;
}

template<class T>
bool Graph<T>::hasEdge(int sID, int eID) {
    for (Edge<T> edge:edges) {
        if (edge.getStart()->getID() == sID &&
            edge.getEnd()->getID() == eID) {
            return true;
        }
    }
    return false;
}


template<class T>
bool Graph<T>::delEdge(int sID, int eID) {
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if ((*it)->getStart()->getID() == sID &&
            (*it)->getEnd()->getID() == eID) {
            edges.erase(it);
            return true;
        }
    }
    return false;
}

template<class T>
Graph<T> *Graph<T>::DFS(int sID) {
    Graph<T> *tree = new Graph<T>();
    std::vector<Edge<T> *> restEdge;
    std::vector<Node<T> *> visitedNode;
    DFSHelper(tree, restEdge, visitedNode);
    return tree;
}

template<class T>
void Graph<T>::DFSHelper(Graph<T> *tree, std::vector<Edge<T> *> &restEdge, std::vector<Node<T> *> &visitedNode) {
    if (restEdge.size() != 0) {
        
    }
}


#endif //GRAPH_GRAPH_H
