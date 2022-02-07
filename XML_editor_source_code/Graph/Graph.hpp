#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <QDebug>
#include "XML_to_JSON/User.hpp"
#include <iostream>

const int NULL_EDGE = 0;
class Graph
{
public:
    Graph(int maxV,vector<User> users);
    bool isEmpty() const;
    bool isFull() const;
    vector<string> build_graph();
    void addVertex(int vertex);
    void addEdge(int fromVertex,int toVertex);
    User most_influencer_user();
    User most_active_user();
    User user_from_id(int id);
	void print();
    ~Graph();

private:
    int numVertices;
    int maxVertices;
    int* vertices;
    int** edges;
    vector<User> users;
};

#endif // GRAPH_HPP
