#include "Node.hpp"

Node::Node()
{
}

Node::Node(string name) 
    : name{ name }{}


Node* Node::addChild(string tagName)
{
    Node* child = new Node(tagName);
    children.push_back(child);
    child->parent = this;
    return child;
}
Node::~Node() {
    for(auto p : children) {
        delete p;
    }
}


