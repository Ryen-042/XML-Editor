#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// tag struct to hold name and attributes of a tag element in XML
typedef struct
{
    string name;
    vector<pair<string, string>> attr;
} tag;

/*
 * class Node is basic element of a Tree
 * used to build a tree of XML Nodes
 *
 */
class Node
{

public:
    // name of the tag
    string name = "";
    // its content
    string value = "";
    // its attributes
    string attributes = "";
    // helper for find and print methods
    bool found = false;
    // parent of that tag
    Node* parent = nullptr;
    // children of a tag
    vector<Node*> children;
    // no arg constractor
    Node();
    // one arg constractor
    Node(string name);
    
    
    /*
     * add child to this Node and set its 
     * parent to this Node
     *
     * @param tagName: name of the Node that will be 
     * created
     * @output child: return pointer to the node 
     * that is been created
     */
    Node* addChild(string tagName);
    
    
    // destructor
    ~Node();
};

#endif // NODE_HPP
