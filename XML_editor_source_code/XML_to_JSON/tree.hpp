#ifndef TREE_H
#define TREE_H

#include "Node.hpp"

/*
 * used to bulid a tree of XML XMLNodes
 *
 */
class Tree
{
private:
    // root of the XML tree
    XMLNode* root;
    
    
    /*
     * helper method to make indentation spaces
     */
    string ind(int depth);
    
    /*
     * parse tag name and its attributes from a string
     *
     * @param s1: string that contain all attributes of a tag
     * @param name: name of the tag
     * @output t: tag that has been paresd
     */
    tag get_tag_struct(string s1, string name);
    
    
    
    /*
     * helper method to print attribute of an element
     *
     * @param s: vector of pair(key,value)
     * as each attribute is key and value
     * @parm depth: used to make correct indentation
     */
    void print_attr(vector<pair<string, string>> s, int depth);

    /*
     * helper method to know all tags that
     * are the same
     *
     * @param r: pointer to the root element of the tree
     * @param ind: level of indentation
     * @param index : output of index of all tags that at that
     * has the same  tag name
     */
    void get_same_tag(XMLNode* r, int ind, vector<int>& index);


    /*
     * private method that used by Print_json method
     * print Tree as a json format using cout object
     *
     * @param r: pointer to the root element
     * @param flag: helper to know where to stop
     */
    void _print_json(XMLNode* r, bool flag);


    /*
     * private method that used by print_xml method
     * it prints Tree as a XML format using cout object
     *
     * @param root: pointer to the root element
     * @param level: used to make correct indentation
     */
    void _print_xml(XMLNode* root, int level);

    /*
     * private method that used by minifing method
     * it prints Tree as a XML format using cout object
     * without any exta spaces and new lines
     *
     * @param root: pointer to the root element
     */
    void _minifing(XMLNode* root);

public:

    // no arg constructor
    Tree();
    
    
    /*
     * parse xml string and convert it to a
     * XML_Tree of XMLNodes
     *
     * @param xml_file: the xml string that will be parsed
     *
     */
    void parse_and_bulid_xml_tree(const std::string& xml);

    /*
     * the public version of _print_xml
     * it prints Tree as a XML format using cout object
     *
     */

    void print_xml();

    /*
     * the public version of _minifing
     * it prints Tree as a XML format using cout object
     * without any exta spaces and new lines
     *
     */
    void minifing();
    
    
    /*
     * the public version of _Print_json
     * it prints Tree as a JSON format using cout object
     *
     */
    void print_json();
    /*
     * pubilc interface with other classes
     * it call method that converts XML to JSON
     *
     * @param xml_file: the xml string that will be converted to json
     * @output json_file: a string that has the conveted text as json format
     */

    string convert_to_json();

    // destructor for the tree which call
    // destructor for XMLNode class
    ~Tree();
};

#endif // TREE_H
