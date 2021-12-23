#include "Node.hpp"

XMLNode::XMLNode()
{
}

XMLNode::XMLNode(string name)
    : name{ name }{}


XMLNode* XMLNode::addChild(string tagName)
{
    XMLNode* child = new XMLNode(tagName);
    children.push_back(child);
    child->parent = this;
    return child;
}
XMLNode::~XMLNode() {
    for(auto p : children) {
        delete p;
    }
}


