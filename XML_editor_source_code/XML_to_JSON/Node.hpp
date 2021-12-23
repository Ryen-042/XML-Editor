#ifndef XMLNode_HPP
#define XMLNode_HPP

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
 * class XMLNode is basic element of a Tree
 * used to build a tree of XML XMLNodes
 *
 */
class XMLNode
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
    XMLNode* parent = nullptr;
    // children of a tag
    vector<XMLNode*> children;
    // no arg constractor
    XMLNode();
    // one arg constractor
    XMLNode(string name);
    
    
    /*
     * add child to this XMLNode and set its
     * parent to this XMLNode
     *
     * @param tagName: name of the XMLNode that will be
     * created
     * @output child: return pointer to the XMLNode
     * that is been created
     */
    XMLNode* addChild(string tagName);
    
    
    // destructor
    ~XMLNode();
};

#endif // XMLNode_HPP
