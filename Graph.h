//
// Created by Thoxvi on 2017/6/8.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H


#include <vector>
#include <algorithm>


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

    Node<T> *getAnOtherNode(Node<T> *one) {
        if (isStart(*one)) {
            return getEnd();
        } else if (isEnd(*one)) {
            return getStart();
        }
        return nullptr;
    }

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

    bool isMyNode(Node<T> &nodeA, Node<T> &nodeB) {
        return isMyNode(nodeA) && isMyNode(nodeB);
    }

    bool isDouble(Node<T> &nodeA, Node<T> &nodeB) {
        return isMyNode(nodeA) && isMyNode(nodeB);
    }

    bool operator<(const Edge<T> &edge) const {
        return power < edge.getPower();
    }

    bool operator==(const Edge<T> &edge) const {
        return edge.getStart()->getID() == getStart()->getID() && edge.getEnd()->getID() == getEnd()->getID();
    }

    //Setter && Getter
    Node<T> *getStart() const {
        return start;
    }

    void setStart(Node<T> *start) {
        Edge::start = start;
    }

    Node<T> *getEnd() const {
        return end;
    }

    void setEnd(Node<T> *end) {
        Edge::end = end;
    }

    int getPower() const {
        return power;
    }

    void setPower(int power) {
        Edge::power = power;
    }
};

template<class T>
class Graph {
private:
    std::vector<Edge<T> *> edges;

    void DFSHelper(Graph *tree, Graph<T> &restEdge, std::vector<Node<T> *> &visitedNode);

    void BFSHelper(Graph *tree, std::vector<Edge<T> *> &spareEdge, std::vector<Node<T> *> &visitedNode);

    bool isNodeInList(Node<T> *node, std::vector<Node<T> *> &list) {
        if (node == nullptr)return false;
        for (Node<T> *tmpNode:list) {
            if (node->same(*tmpNode)) {
                return true;
            }
        }
        return false;
    }

public:
    Graph() {};

    void addNode(T data);

    void addNode(Node<T> *node);

    void addEdge(T start, T end, int power);

    void addEdge(Node<T> *start, Node<T> *end, int power);

    void addEdge(Edge<T> *edge);

    std::vector<Node<T> *> getAllNodeFromEdges();

    std::vector<Edge<T> *> getEdgesIfNodeIn(int ID);

    std::vector<Edge<T> *> getEdgeIfNodeStart(int ID);

    std::vector<Edge<T> *> getEdgeIfNodeEnd(int ID);

    Node<T> *getNodeByID(int ID);

    bool hasEdge(int sID, int eID);

    bool hasEdge(Edge<T> *edge);

    bool delEdge(int sID, int eID);

    bool delEdge(Edge<T> *del);

    //深度优先遍历
    Graph<T> *DFS(int sID);

    //广度优先遍历
    Graph<T> *BFS(int sID);

    //Getter & Setter
    std::vector<Edge<T> *> *getEdges() {
        return &edges;
    }

    void setEdges(const std::vector<Edge<T> *> &edges) {
        Graph::edges = edges;
    }

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
std::vector<Edge<T> *> Graph<T>::getEdgesIfNodeIn(int ID) {
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
    for (Edge<T> *edge:edges) {
        if (edge->getStart()->getID() == sID &&
            edge->getEnd()->getID() == eID) {
            return true;
        }
    }
    return false;
}

template<class T>
bool Graph<T>::hasEdge(Edge<T> *edge) {
    for (Edge<T> *tedge:edges) {
        if (tedge->isDouble(*edge->getStart(), *edge->getEnd())) {
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
bool Graph<T>::delEdge(Edge<T> *del) {
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if ((*it)->isDouble(*del->getStart(), *del->getEnd())) {
            edges.erase(it);
            return true;
        }
    }
    return false;
}

template<class T>
Graph<T> *Graph<T>::DFS(int sID) {
    Graph<T> *tree = new Graph<T>();
    std::vector<Node<T> *> visitedNode = std::vector<Node<T> *>();

    Graph<T> restEdge = Graph<T>();
    for (Edge<T> *edge:edges) {
        restEdge.addEdge(edge);
    }

    Node<T> *next = getNodeByID(sID);
    visitedNode.push_back(next);

    DFSHelper(tree, restEdge, visitedNode);
    return tree;
}

template<class T>
Graph<T> *Graph<T>::BFS(int sID) {
    Graph<T> *tree = new Graph<T>();
    std::vector<Node<T> *> visitedNode = std::vector<Node<T> *>();
    std::vector<Edge<T> *> disableEdge = std::vector<Edge<T> *>();
    std::vector<Edge<T> *> spareEdge = std::vector<Edge<T> *>();
    Node<T> *next = getNodeByID(sID);
    visitedNode.push_back(next);

    do {
        Node<T> *now = *(visitedNode.end() - 1);
        std::vector<Edge<T> *> sideEdges = getEdgesIfNodeIn(now->getID());
        Graph<T> mixEdges = Graph();

        mixEdges.getEdges()->insert(mixEdges.getEdges()->begin(), tree->getEdges()->begin(), tree->getEdges()->end());
        mixEdges.getEdges()->insert(mixEdges.getEdges()->begin(), spareEdge.begin(), spareEdge.end());
        mixEdges.getEdges()->insert(mixEdges.getEdges()->begin(), disableEdge.begin(), disableEdge.end());


        std::vector<Edge<T> *> tmpEdges = std::vector<Edge<T> *>();

        for (Edge<T> *edge:sideEdges) {
            if (!mixEdges.hasEdge(edge)) {
                tmpEdges.push_back(edge);
            }
        }
        spareEdge.insert(spareEdge.end(), tmpEdges.begin(), tmpEdges.end());
        std::sort(spareEdge.begin(), spareEdge.end());
        Edge<T> *minEdge = *(spareEdge.begin());
        spareEdge.erase(spareEdge.begin());
        for (Node<T> *node:visitedNode) {
            if (minEdge->isMyNode(*node)) {
                Node<T> *anOther = minEdge->getAnOtherNode(node);
                //检测无效边
                if (isNodeInList(anOther, visitedNode)) {
                    disableEdge.push_back(minEdge);
                    break;
                }
                tree->addEdge(minEdge);
                visitedNode.push_back(anOther);
                break;
            }
        }

    } while ((tree->getEdges()->size() + disableEdge.size()) < this->getEdges()->size());


    return tree;
}

template<class T>
void
Graph<T>::DFSHelper(Graph<T> *tree, Graph<T> &restEdge, std::vector<Node<T> *> &visitedNode) {
//    Node<T> *now = *(visitedNode.end() - 1);
//    std::vector<Edge<T> *> sideEdge;
//    for (Edge<T> *edge:restEdge) {
//        Node<T> *anoutherNode = edge->getAnOtherNode(now);
//        if (!isNodeInList(anoutherNode, visitedNode)) {
//            sideEdge.push_back(edge);
//        }
//    }
//    std::sort(sideEdge.begin(), sideEdge.end());
//    for (Edge<T> *tmpEdge:sideEdge) {
////        if (tree->hasEdge(tmpEdge)) continue;
//        tree->addEdge(tmpEdge);
//        if (tmpEdge->isStart(*now)) {
//            visitedNode.push_back(tmpEdge->getEnd());
//        } else {
//            visitedNode.push_back(tmpEdge->getStart());
//        }
//        for (auto it = restEdge.begin(); it != restEdge.end(); ++it) {
//            if ((*it) == tmpEdge) {
//                restEdge.erase(it);
//                break;
//            }
//        }
//        DFSHelper(tree, restEdge, visitedNode);
//
//    }

    Node<T> *now = *(visitedNode.end() - 1);
    auto tmpEdges = restEdge.getEdgesIfNodeIn(now->getID());
    std::sort(tmpEdges.begin(), tmpEdges.end());
    for (auto minEdge:tmpEdges) {
        auto anOtherNode = minEdge->getAnOtherNode(now);
        if (!isNodeInList(anOtherNode, visitedNode)) {
            tree->addEdge(minEdge);
            restEdge.delEdge(minEdge);
            visitedNode.push_back(anOtherNode);
            DFSHelper(tree, restEdge, visitedNode);
        }
    }
}

template<class T>
void
Graph<T>::BFSHelper(Graph<T> *tree, std::vector<Edge<T> *> &spareEdge, std::vector<Node<T> *> &visitedNode) {
    Node<T> *now = *(visitedNode.end() - 1);
    std::vector<Edge<T> *> sideEdges = tree->getEdgesIfNodeIn(now->getID());
    spareEdge.insert(sideEdges.end(), sideEdges.begin(), sideEdges.end());
    std::sort(spareEdge.begin(), spareEdge.end());
    spareEdge.erase(std::unique(spareEdge.begin(), spareEdge.end()), spareEdge.end());


}


#endif //GRAPH_GRAPH_H
